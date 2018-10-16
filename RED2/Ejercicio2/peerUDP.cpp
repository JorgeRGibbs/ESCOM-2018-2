#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>

#define KYEL	"\x1B[33m"
#define KRED	"\x1B[31m"
#define KGRN	"\x1B[32m"
#define RESET	"\x1B[0m"

#define SIZE_BUFFER 250

using namespace std;

int getFileSize(ifstream *file){
       file->seekg(0,ios::end);
       int filesize = file->tellg();
       file->seekg(ios::beg);
       return filesize;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

struct datos{
	const char* puertoPadre;
	u_short puerto;
	const char* codigoOperacion;
    const char* nombreArchivo;
    int parte;
    int total;
};

struct datosCliente{
	
	u_short puerto;
	int *idCanal;
};

char* getIP(){
	
	char hostbuffer[256];
	char *IPbuffer;
	struct hostent *host_entry;
	int hostname;
		
	hostname = gethostname(hostbuffer,sizeof(hostbuffer));
	
	host_entry = gethostbyname(hostbuffer);
	
	IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
	
	return IPbuffer;
}



int puerto,idSocket;
string ip,operacion;
struct sockaddr_in servidor;

int realizarOperacionS(const char* codigo,u_short puerto, string archivo,int parte,int total);
void realizarOperacion(const char* codigo);
void correHiloNuevo(int clienteSocket);
void * peticionCliente( void* );
void * interfaz( void* );
void * conectarPeer( void* );
void * acceptCiclo(void* );

int main( int argc, char const *argv[] ){
    
	int primero,reuse,aux;
	
	idSocket = socket(AF_INET,SOCK_DGRAM,0);
	
	if(idSocket == -1){
		
		perror("Error al crear el socket");
		exit(EXIT_FAILURE);	
	}
	
	memset(&servidor,sizeof(servidor),0);
	
	if(argc < 1){
		
		perror("Error falta un argumento");
		exit(EXIT_FAILURE);
	}
	
	primero = atoi( argv[1] );
	
	if(primero == 1){
		
		int as = atoi( argv[2] );
		servidor.sin_family = AF_INET;
		servidor.sin_port = htons( as );
		servidor.sin_addr.s_addr = INADDR_ANY;
			
	}else{
		
		ifstream nodos;
		nodos.open("nodos.txt");
		servidor.sin_family = AF_INET;
		nodos >> aux;
		
		if(aux == 0){
			
			int pAux;
			nodos >> pAux;
			servidor.sin_port = htons(pAux);
			servidor.sin_addr.s_addr = INADDR_ANY;
			nodos.close();	
			ip = to_string(servidor.sin_addr.s_addr);
			puerto = servidor.sin_port;
			ip = to_string(servidor.sin_addr.s_addr);
			puerto = ntohs(servidor.sin_port);
		}else{
			
			perror("Error al leer el archivo nodos.dat");
			exit(EXIT_FAILURE);
		}
		
	}
	
	reuse = 1;
	if(setsockopt(idSocket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int))<0){
		
		perror("Error al realizar el SO_REUSEADDR");
		exit(EXIT_FAILURE);	
	}
	
	if(setsockopt(idSocket,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(int))<0){
		
		perror("Error al realizar el SO_REUSEPORT");
		exit(EXIT_FAILURE);	
	}
	
	if(bind(idSocket,(struct sockaddr *)&servidor,sizeof(servidor))==-1){
		
		perror("Error al realizar el bind");
		exit(EXIT_FAILURE);		
	}
	
	if(primero == 1){
		
		ofstream nodos;
		nodos.open("nodos.txt");
		struct sockaddr_in sin;
		socklen_t len = sizeof(sin);
		
		if (getsockname(idSocket, (struct sockaddr *)&sin, &len) == -1)
	    	perror("getsockname");
		else
			puerto = ntohs(sin.sin_port);
		
		ip = to_string(servidor.sin_addr.s_addr);
		puerto = ntohs(servidor.sin_port);
		nodos << "0 " << puerto << " " << ip << endl;
		nodos.close();
	}
	
	
	
	pthread_t interfazHilo;
	pthread_create(&interfazHilo,NULL,interfaz,NULL);
	operacion = "x";
	
	pthread_t acceptHilo;
	pthread_create(&acceptHilo,NULL,acceptCiclo,NULL);
	
	pthread_join(interfazHilo,NULL);
	pthread_join(acceptHilo,NULL);
	
	return 0;
}
vector<string> filesNew;
void * interfaz( void* ){
	
	
	string atributo;
	system("clear");
	printf("%s----------------------------------------------------%s\n",KYEL,RESET);
	printf("\t%sPEER%s---------->%sIP:%s LOCAL_IP %sPUERTO:%s %d\n",KRED,RESET,KYEL,RESET,KYEL,RESET,puerto);
	printf("%s----------------------------------------------------%s\n",KYEL,RESET);
	
	while(operacion.compare("salir")!=0){
				
			if(operacion.compare("status")==0){
				
				string a = "0";
				realizarOperacion(a.c_str());
				
			}else if(operacion.compare("actualiza")==0){
				
					
					ofstream archivoLista;
					archivoLista.open("lista.txt");
					
					string dir = string("archivos");
    				
					filesNew = vector<string>();
					
    				getdir(dir,filesNew);

    				for (unsigned int i = 0;i < filesNew.size()-2;i++) {
        				archivoLista << filesNew[i] << endl;
    				}
					archivoLista.close();
					string a = "1";
					realizarOperacion(a.c_str());	
				
			}else if(operacion.compare("descargar")==0){
			
				string des = "2";
                vector<int> puerto = vector<int>();
                int *parte;
                string dir = string("listasArchivos");
    			vector<string> listasArch = vector<string>();
				getdir(dir,listasArch);
                string nombreArchivo;
                ifstream archivoLista;
                for (unsigned int i = 0;i < listasArch.size()-2;i++) {
                        bool fg = true;
                        string dirTemp = "listasArchivos/",nombreTemp,cadena;
                        dirTemp.append(listasArch[i]);
                        nombreTemp = listasArch[i];
        				nombreTemp.erase(nombreTemp.end()-4,nombreTemp.end());
                        cout << "Archivos en el peer " << nombreTemp << ":" << endl;
                        archivoLista.open(dirTemp.c_str());
                        archivoLista >> cadena;
                        while(archivoLista||fg){    
                            cout << cadena << endl;
                            archivoLista >> cadena;
                            fg = false;
                        }
                        archivoLista.close();
    			}
                cout << "Descargar archivo: ";
                cin >> nombreArchivo;
                for (unsigned int i = 0;i < listasArch.size()-2;i++) {
                        bool fg = true;
                        string nombreTemp = "listasArchivos/",cadena;
                        nombreTemp.append(listasArch[i]);
        				listasArch[i].erase(listasArch[i].end()-4,listasArch[i].end());
                        archivoLista.open(nombreTemp.c_str());
                        archivoLista >> cadena;
                        while(archivoLista||fg){
                            if(nombreArchivo.length()==cadena.length())
                                if(nombreArchivo.compare(cadena)==0){
                                    puerto.push_back(atoi(listasArch[i].c_str()));  
                                }
                            fg = false;
                            archivoLista >> cadena;
                        }
                        archivoLista.close();
    			}
                int *num = (int *) malloc(sizeof(int)*puerto.size()),descargado;
                for(int i = 0; i < puerto.size(); i++){
                    num[i] = i;
                    descargado = realizarOperacionS(des.c_str(),puerto[i],nombreArchivo,num[i],puerto.size());
                    cout << "Recibido paquete del puerto: " << puerto[i] << endl;
                }
                string filename = "descargas/";
                filename.append(nombreArchivo);
                ofstream archivoDescargado;
                archivoDescargado.open(filename,ios::out|ios::binary);
                string fileTemp;
                cout << "Descargando...";
                for(int i = 0; i < puerto.size(); i++){
                    
                    fileTemp.clear();
                    fileTemp.append("temp/");
                    fileTemp.append(nombreArchivo);
                    fileTemp.append(to_string(i));
                    fileTemp.append(".prt");
                    ifstream temp;
                    temp.open(fileTemp.c_str(),ios::in|ios::binary);
                    int filesize = getFileSize(&temp);
                    char *inputBuffer = new char[filesize];
                    temp.read(inputBuffer,filesize);
                    archivoDescargado.write(inputBuffer,filesize);
                    temp.close();
                    //remove(fileTemp.c_str());
                    
                }
               archivoDescargado.close();
               chmod(filename.c_str(),0777);
               cout << "FIN" << endl;
                
		}
		printf("> ");
		cin >> operacion;
	}
	
	exit(0);
	pthread_exit(NULL);
}

void realizarOperacion(const char* codigo){
	
	string basura;
	ifstream nodos;
	int numeroNodo;
	nodos.open("nodos.txt");
	nodos >> numeroNodo;
	string puertoTemp;			
	while(nodos){
					
		struct datos *datosPeer = (struct datos *) malloc(sizeof(struct datos));
		if(numeroNodo!= 0){
			datosPeer->puertoPadre = puertoTemp.c_str();
			nodos >> datosPeer->puerto;
			nodos >> basura;
			datosPeer->codigoOperacion = codigo;
			pthread_t conectarHilo;
			pthread_create(&conectarHilo, NULL, conectarPeer,datosPeer);
					
		}else{
						
			nodos >> puertoTemp;
			nodos >> basura;
		}
					
			nodos >> numeroNodo;
	}
    nodos.close();
}

int realizarOperacionS(const char* codigo,u_short puerto, string archivo,int parte,int total){
	
	    
		struct datos *datosPeer = (struct datos *) malloc(sizeof(struct datos));
		
        datosPeer->puertoPadre = to_string(puerto).c_str();
		
        datosPeer->puerto = puerto;
				
        datosPeer->codigoOperacion = codigo;
  
        datosPeer->nombreArchivo = archivo.c_str();
            
        datosPeer->parte = parte;
            
        datosPeer->total = total;
    
	    pthread_t conectarHilo;
		pthread_create(&conectarHilo, NULL, conectarPeer,datosPeer);
    
        pthread_join(conectarHilo,NULL);
}

void * conectarPeer( void* peerH){
	
	const char* codigoOperacion = ((struct datos*)peerH)->codigoOperacion;
	struct sockaddr_in peer;
	memset(&peer,sizeof(peer),0);
	peer.sin_port = htons(((struct datos*)peerH)->puerto);
	peer.sin_addr.s_addr = INADDR_ANY;
	int *idSocketPeer = (int*)malloc(sizeof(int));
	int brecv,bsent;
	*idSocketPeer = socket(AF_INET,SOCK_DGRAM,0);
	char * baf;
	const char* puertoPad = ((struct datos*)peerH)->puertoPadre;
	if(*idSocketPeer == -1){
		
		printf("Error al crear el socket\n");
		pthread_exit(NULL);	
	}
	
//	if(connect(*idSocketPeer,(struct sockaddr *)&peer,sizeof(peer))==-1){
		
//		printf("%sConexion fallida peer: Ip: LOCAL_IP Puerto: %d %s\n",KRED,ntohs(peer.sin_port),RESET);
//	}else{
		//socklen_t peerlen = (const socklen_t) sizeof (peer);
		printf("%sConexion exitosa peer: Ip: LOCAL_IP Puerto: %d %s\n",KGRN,ntohs(peer.sin_port),RESET);
		bsent = sendto(*idSocketPeer,codigoOperacion,strlen(codigoOperacion),0,&peer,sizeof(peer));
    	//n = sendto(sockfd, buf, strlen(buf), 0, &serveraddr, serverlen);
        brecv = recv(*idSocketPeer,baf,SIZE_BUFFER,0);
    	//n = recvfrom(sockfd, buf, strlen(buf), 0, &serveraddr, &serverlen);
        
		if(send(*idSocketPeer,puertoPad,strlen(puertoPad),0)==-1)
            cout << "Error send" << endl;
		int codigo = atoi(codigoOperacion);
		
		if(codigo == 1){
            
            int input_file = open("lista.txt", O_RDONLY );
			while (1) {
				char buffer[SIZE_BUFFER];
    			int bytes_read = read(input_file, buffer, sizeof(buffer));
    			if (bytes_read == 0) 
					break;
    			if (bytes_read < 0) {
        
    			}

	    		void *p = buffer;
    			while (bytes_read > 0) {
        			int bytes_written = write(*idSocketPeer, p, bytes_read);
        			if (bytes_written <= 0) {
            		    cout << "que pedo" << endl;
        			}
        		    bytes_read -= bytes_written;
        	        p += bytes_written;
    			}
                if(SIZE_BUFFER>bytes_read){
                    break;   
                }
			}
            close(input_file);
            
			
		//}else if(codigo == 2){
            
            const char* nomArchivo = ((struct datos*)peerH)->nombreArchivo;
            if(write(*idSocketPeer,nomArchivo,strlen(nomArchivo))==-1){
                perror("Send nombre archivo");
                exit(-1);
            }
            const char *parte = to_string(((struct datos*)peerH)->parte).c_str();
            int parteT = atoi(parte);
            write(*idSocketPeer,"#",sizeof(char));
            if(write(*idSocketPeer,parte,strlen(parte))==-1){
                perror("Send parte");
                exit(-1);
            }
            const char *total = to_string(((struct datos*)peerH)->total).c_str();
			write(*idSocketPeer,"#",sizeof(char));
            if(write(*idSocketPeer,total,strlen(total))==-1){
                perror("Send total");
                exit(-1);
            }
            write(*idSocketPeer,"#",sizeof(char));
            
            string an = "temp/";
            an+=nomArchivo;
            an.append(to_string(parteT));
            an.append(".prt");
            //int input_file = open(an.c_str(), O_WRONLY |O_CREAT | O_TRUNC,0666);
            int totalCont=0;
            int contAUS = 0;
			while (1) {
				char bufferr[SIZE_BUFFER];
    			int bytes_read = recv(*idSocketPeer, bufferr, SIZE_BUFFER,0);
    			if (bytes_read == 0) 
					break;
    			if (bytes_read < 0) {
                    perror("Read ");
                    exit(-1);
    			}
                
                if(bufferr[0]=='@' && contAUS<1){
                    contAUS++;
                    continue;
                    
                }
                    
	    		void *p = bufferr;
                //cout << bufferr << endl;
                if(bytes_read!= 250){
                 //cout << "ALERTA!" << endl;   
                }
                totalCont += bytes_read;
                //cout << totalCont << endl;
                //cout << bytes_read << endl;
    			while (bytes_read > 0) {
        			int bytes_written = write(input_file, p, bytes_read);
        			if (bytes_written <= 0) {
            		    perror("Write ");
                        exit(-1);
        			}
        		    bytes_read -= bytes_written;
        		    p += bytes_written;
    			}
                if(SIZE_BUFFER>bytes_read){
                    //break;   
                }
                //
			}
            close(input_file);
		}
	//}
	
	pthread_exit(NULL);
}

void * acceptCiclo(void* ){
	
	struct sockaddr_in cliente;
	socklen_t tamanoCliente = (socklen_t) sizeof(cliente);
	while(true){
		int *idCanal = (int*) malloc(sizeof(int));
		*idCanal = accept(idSocket,(struct sockaddr *)&cliente,&tamanoCliente);
		if(*idCanal == -1){
			
			perror("Error al realizar el accept");
			exit(-1);
			
		}else{
			
			pthread_t hilo;
			if(pthread_create(&hilo, NULL, peticionCliente,idCanal)==-1){
				perror("Phtread_Create");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	pthread_exit(NULL);
}

void * peticionCliente( void* datosC){
	
	char buffer[SIZE_BUFFER];
	int *idCanal = (int *) datosC;
	int caracteresRecibidos,enviado;
	int codigo=0,port=0;
	
	char mensaje[SIZE_BUFFER];
		
	caracteresRecibidos = recv(*idCanal,buffer,SIZE_BUFFER,0);
	buffer[caracteresRecibidos] = '\0';
	codigo = atoi(buffer);
	
    send(*idCanal,"@",sizeof(char),0);
    
    caracteresRecibidos = recv(*idCanal,mensaje,SIZE_BUFFER,0);
	mensaje[caracteresRecibidos] = '\0';
	port = atoi(mensaje);
    
	if(codigo==1){
            
            string an = "listasArchivos/";
            an.append(to_string(port));
            an.append(".txt");
            int input_file = open(an.c_str(), O_WRONLY |O_CREAT | O_TRUNC,0666);
			while (1) {
				char bufferr[SIZE_BUFFER];
    			int bytes_read = read(*idCanal, bufferr, sizeof(bufferr));
    			if (bytes_read == 0) 
					break;
    			if (bytes_read < 0) {
                    perror("Read ");
                    exit(-1);
    			}

	    		void *p = bufferr;
    			while (bytes_read > 0) {
        			int bytes_written = write(input_file, p, bytes_read);
        			if (bytes_written <= 0) {
            		
        			}
        		    bytes_read -= bytes_written;
        		    p += bytes_written;
    			}
                if(SIZE_BUFFER>bytes_read){
                    break;   
                }
                //
			}
            close(input_file);
			
		
	}else if(codigo==2){ 
        
        cout << "Solicitud recibida" << endl;
        
        cout << "Datos a enviar: " << endl;
        caracteresRecibidos = recv(*idCanal,mensaje,SIZE_BUFFER,0);
	    mensaje[caracteresRecibidos] = '\0';
	    string nombreArchivo = mensaje;
        //nombreArchivo.append(mensaje);
        string aux = "";
        bool fg = false,fx = true;
        int cont = 0,fin=0,parte,total;
        for(int i = 0; i < nombreArchivo.length(); i++){
            if(fg&&nombreArchivo[i]!='#'){
                aux += nombreArchivo[i];
            }
            if(nombreArchivo[i]=='#'&&!fg){
                fg = true;
                if(fx){
                    fin = i;
                    fx = false;
                }
            }else if(fg&&nombreArchivo[i]=='#'&&cont==0){
                parte = atoi(aux.c_str());
                aux = "";
                cont++;
            }else if(fg&&nombreArchivo[i]=='#'&&cont==1){
                total = atoi(aux.c_str());
                aux = "";
                cont++;
            }
        }
        nombreArchivo.erase(nombreArchivo.begin()+fin,nombreArchivo.end());
        string ubiArchivo = "archivos/";
        ubiArchivo.append(nombreArchivo);
        cout << "Nombre del archivo: " << nombreArchivo << endl;
        
        cout << "Parte: " << parte+1 << "/" << total << endl;
        cout << "ENVIANDO..." << endl;
        struct stat st;
        stat(ubiArchivo.c_str(),&st);
        int tamanioArchivo = st.st_size;
        
        
        int posicionInicio = (tamanioArchivo/total)*parte;
        int posicionMAX = ((tamanioArchivo/total)*(parte+1));
        int atajada = (tamanioArchivo/total);
        int ventana = 0;
        bool bandera = false;
        int contadorTotal = 0;
        if((tamanioArchivo/total)>SIZE_BUFFER){
              ventana = SIZE_BUFFER;
        }else{
              ventana = (tamanioArchivo/total);
        }
        ifstream filestream;
        filestream.open(ubiArchivo.c_str(),ios::in|ios::binary);
        char bufferr[atajada];
        string nuevoArchivo;
        int cuenta = 0;
        ofstream output;
        while(!filestream.eof()){
            nuevoArchivo.clear();
            nuevoArchivo.append("temp/");
            nuevoArchivo.append(nombreArchivo);
            nuevoArchivo.append(to_string(cuenta));
            nuevoArchivo.append(".prt");
            output.open(nuevoArchivo.c_str(),ios::out|ios::trunc|ios::binary);
            if(cuenta+1==total)
                atajada++;
            if(output.is_open()){
                filestream.read(bufferr,atajada);
                output.write(bufferr,filestream.gcount());
                output.close();
                cuenta++;
            }
        }
        string auxx = nombreArchivo;
        filestream.close();
        nombreArchivo.clear();
        nombreArchivo.append("temp/");
        nombreArchivo.append(auxx);
        nombreArchivo.append(to_string(parte));
        nombreArchivo.append(".prt");
        int totalCont = 0;
        int input_file = open(nombreArchivo.c_str(), O_RDONLY );
        
			while (1) {
				char buffer[SIZE_BUFFER];
    			int bytes_read = read(input_file, buffer, sizeof(buffer));
    			if (bytes_read == 0) 
					break;
    			if (bytes_read < 0) {
                    perror("Read ");
                    exit(-1);
    			}

	    		void *p = buffer;
                
    			while (bytes_read > 0) {
        			int bytes_written = write(*idCanal, p, bytes_read);
        			if (bytes_written <= 0) {
            		    perror("write ");
                        exit(-1);
        			}
                    if(bytes_written!=250){
                        //cout << "ALERTA" << endl;   
                    }
                    totalCont += bytes_written;
                    //cout << totalCont << endl;
                    //cout << bytes_written << endl;
        		    bytes_read -= bytes_written;
        	        p += bytes_written;
    			}
                if(SIZE_BUFFER>bytes_read){
                   // break;   
                }
			}
            close(input_file);
            
        while(--cuenta>=0){
            
            nombreArchivo.clear();
            nombreArchivo.append("temp/");
            nombreArchivo.append(auxx);
            nombreArchivo.append(to_string(cuenta));
            nombreArchivo.append(".prt");
            //remove(nombreArchivo.c_str());
        }
        cout <<  "ENVIADO" << endl;
			
	}else if(codigo == 0){
		
	}
	close(*idCanal);
	pthread_exit(NULL);
}

