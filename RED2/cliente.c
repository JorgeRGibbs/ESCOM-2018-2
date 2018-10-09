#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>



int main(int argc, char **argv)
{	
	int ServS,port,idCanal,validarListen,nCar;
	struct sockaddr_in servidor;
	struct hostent *server;
	char buffer[50];
	port = atoi(argv[2]);

	//SECCION DE CONFIGURACION
	ServS = socket(AF_INET,SOCK_STREAM,0);
	printf("Puerto:%d \n", port);
	//Paso 1: Creación del socket usando AF_INET
	if (!ServS){perror("Error al crear el socket");exit(EXIT_FAILURE);}
	printf("socket del cliente generado correctamente\n");
	//Paso numero 2 llenamos la estructura del servidor y después publicamos el servicio
	server = gethostbyname(argv[1]);
	if (!server){perror("No existe el host");exit(EXIT_FAILURE);}
	memset(&servidor,sizeof(servidor), 0);
	//bzero((char*)&servidor, sizeof(servidor));
	//memset(&servidor,sizeof(servidor), 0);
	//Reinicializando la estructura
	//Puertos no deben de ser menor a 1024 
	//INADDR asigna la interfaz de red por default
	servidor.sin_family = AF_INET;
	/*
	bcopy((char *)server->h_addr,
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);*/
	servidor.sin_addr.s_addr 
		= inet_addr(inet_ntoa(*(struct in_addr*)*server->h_addr_list));
	servidor.sin_port = htons ( port );

	int Conn = connect(ServS,(struct sockaddr*)&servidor,sizeof(servidor));
	//Note: cast to sockaddr_in* if not working
	if (Conn == -1){perror("Error en la conexión");exit(EXIT_FAILURE);}
	printf("CONFIGURACION COMPLETA");
	// Comienza fase de comunicación
	int in,out;
	while(1)
    {
        char datos[50];
        //getline(cin, data);
        memset(&buffer, 0, sizeof(buffer));//clear the buffer
        strcpy(buffer,datos );
        if(datos == "fin")
        {
            send(idCanal, (char*)&buffer, strlen(buffer), 0);
            break;
        }
        out += send(idCanal, (char*)&buffer, strlen(buffer), 0);
        printf("Esperando respuesta del servidor...\n");
        memset(&buffer, 0, sizeof(buffer));//clear the buffer
        in += recv(idCanal, (char*)&buffer, sizeof(buffer), 0);
        if(!strcmp(buffer, "fin"))
        {
        	printf("Sesión terminada\n");
            break;
        }
        printf("Servidor:\n");
    }
	close(ServS);

/*	while(1)
    {
        //string data;
        //char *msg;
        fgets(buffer,50,stdin);
        memset(&buffer, 0, sizeof(buffer));//clear the buffer
        //strcpy(msg, data.c_str());
        //strcpy(buffer,msg);
        if(buffer == "exit")
        {
            send(ServS, &buffer, strlen(buffer), 0);
            break;
        }
        nCar = send(ServS, &buffer, strlen(buffer), 0);
        printf("Esperando respuesta del servidor...\n");
        memset(&buffer, 0, sizeof(buffer));//clear the buffer
        if(!strcmp(buffer, "exit"))
        {
            printf("El server ha salido\n");
            break;
        }
        printf("Servidor: %s \n",buffer );
        //cout << "Server: " << msg << endl;
    }
        */
	//buffer[nCar] = '\0';
	/*printf("ingrese el mensaje\n");
	bzero(buffer,50);
	fgets(buffer,50,stdin);
	nCar = send(idCanal,buffer,strlen(buffer),0);
	printf("Mensaje recibido del cliente: %s\n",buffer);
	bzero(buffer,50);
	strcpy(buffer,'Hola');
	int nCar = recv(idCanal,buffer,50,0);
	*/

	return 0;
}