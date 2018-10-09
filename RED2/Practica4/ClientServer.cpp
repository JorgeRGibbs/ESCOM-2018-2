#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <pthread.h>
#include <dirent.h>
#include <string>
#include <vector>

void correHiloNuevo(int clienteSocket);
void * peticionCliente( void* );
void showFiles();

/*
struct nodo
{
	uint32_t peso;
	char[64] nombre;
	nodo *sig;
};

class archivos
{
	private:
		nodo *inicio,*fin;
	public:
		archivos()
		{
			inicio = NULL;
			fin = NULL;
		}
		void nuevo(uint32_t peso, char nombre)
		{
			nodo *tmp = new nodo;
			tmp -> peso = peso;
			tmp -> nombre = strcpy(nombre, nombre);
			tmp->sig
		} if (inicio == NULL)
		{
			inicio = tmp;
			fin = tmp;
		}else
		{
			fin -> sig = tmp;
			fin = fin->sig;
		}
}

void Add_files()
{
	printf("Nombre:\n");
	printf("Peso:\n");
	archivos a;
	a.nuevo()
}*/

std::vector <std::string> read_directory( const std::string& path = std::string() )
{
  std::vector <std::string> result;
  dirent* de;
  DIR* dp;
  errno = 0;
  dp = opendir( path.empty() ? "." : path.c_str() );
  if (dp)
    {
    while (true)
      {
      errno = 0;
      de = readdir( dp );
      if (de == NULL) break;
      result.push_back( std::string( de->d_name ) );
      }	
    closedir( dp );
    std::sort( result.begin(), result.end() );
    }
    for(int = 0; i<result.size();i++)
    {
    	cout << result[i]<<endl;
    }

}

int main( int argc, char const *argv[] ){
	
	archivos archivos;
	int idSocket,puerto;
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	//Paso numero 1 creacion de socket, se utiiza AF_INET para comunicarnos por internet y se utiliza SOCK_STREAM
	idSocket = socket(AF_INET,SOCK_STREAM,0);
	
	if(idSocket == -1){
		
		perror("Error al crear el socket");
		exit(EXIT_FAILURE);	
	}

	//Paso numero 2 llenamos la estructura 
	memset(&servidor,sizeof(servidor),0);
	
	puerto = atoi( argv[1] );
	
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons( puerto );
	servidor.sin_addr.s_addr = INADDR_ANY;
	
	int reuse = 1;
	
	setsockopt(idSocket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	setsockopt(idSocket,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(int));
	
	if(bind(idSocket,(struct sockaddr *)&servidor,sizeof(servidor))==-1){
		
		perror("Error al realizar el bind");
		exit(EXIT_FAILURE);		
	
	}
	
	if(listen(idSocket,2)==-1){
		
		perror("Error al realizar el listen");
		exit(EXIT_FAILURE);
	
	}
	
	socklen_t tamanoCliente = (socklen_t) sizeof(cliente);
	
	while(true){
		
		int *idCanal = (int*) malloc(sizeof(int));
		*idCanal = accept(idSocket,(struct sockaddr *)&cliente,&tamanoCliente);
		
		if(*idCanal == -1){
			
			perror("Error al realizar el accept");
			exit(EXIT_FAILURE);
			
		}else{
			
			pthread_t hilo;
			pthread_create(&hilo, NULL, peticionCliente, (void *)idCanal);
		}
	}
	
	return 0;
}

void * peticionCliente( void* socket){
	
	char buffer[50];
	int *idCanal = (int *) socket;
	int caracteresRecibidos,enviado;
	
	while(buffer[0]!='@'){
		
		char mensaje[50];
		caracteresRecibidos = recv(*idCanal,buffer,50,0);
		buffer[caracteresRecibidos] = '\0';
		printf("Cliente %d: %s \n",*idCanal,buffer);
		if(buffer[0]!='@'){
		
			printf("Tu mensaje a %d: ",*idCanal);
			fgets(mensaje,50,stdin);
		
		}else{
			
			mensaje[0] = '@';
			mensaje[1] = '\0';
			printf("El cliente %d acabo\n",*idCanal);
		}
			
		
		enviado = send(*idCanal,mensaje,strlen(mensaje),0);	
	
	}
	close(*idCanal);
	pthread_exit(NULL);
}

