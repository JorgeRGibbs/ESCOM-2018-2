#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{	
	int idSocket,port,idCanal,validarListen;
	port = atoi(argv[1]);
	//SECCION DE CONFIGURACION
	idSocket = socket(AF_INET,SOCK_STREAM,0);
	printf("socket generado correctamente\n");
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	
	printf("Puerto:%d \n", port);
	//Paso 1: Creación del socket usando AF_INET
	if (idSocket == -1)
	{
		perror("Error al crear el socket");
		exit(EXIT_FAILURE);
	}
	//Paso numero 2 llenamos la estructura del servidor y después publicamos el servicio

	memset(&cliente,sizeof(cliente),0 );
	//memset(&servidor,sizeof(servidor), 0);

	//Reinicializando la estructura
	//Puertos no deben de ser menor a 1024 
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons ( port );
	//INADDR asigna la interfaz de red por default
	servidor.sin_addr.s_addr = INADDR_ANY;
	//cliente.sin_addr.s_addr = inet_addr('127.0.0.1');

	int idBind = bind(idSocket,(struct sockaddr_in*)&servidor,sizeof(servidor));
	if (idBind == -1)
	{
		perror("Error en el bind");
		exit(EXIT_FAILURE);
	}

	validarListen = listen(idSocket,2);

	if (validarListen == -1 )
	{
		perror("Error al validar listen");
		exit(EXIT_FAILURE);
	}
	int tam = sizeof(cliente);
	idCanal = accept(idSocket,&cliente,&tam);
	if (idCanal == -1)
	{
		perror("Error en el canal\n");
		exit(EXIT_FAILURE);
	}
	printf("CONFIGURACION COMPLETA");
	// Comienza fase de comunicación

	char buffer[50];
	int nCar = recv(idCanal,buffer,50,0);
	buffer[nCar] = '\0';
	printf("Mensaje recibido del cliente: %s\n",buffer);
	strcpy(buffer,'Hola');
	nCar = send(idCanal,buffer,strlen(buffer),0);
	close(idSocket);

	return 0;
}