#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{	
	int idSocket,port,bind,clienteTam;
	char buffer[50];
	port = atoi(argv[1]);
	//SECCION DE CONFIGURACION
	ServS = socket(AF_INET,SOCK_STREAM,0);
	printf("socket del servidor generado correctamente\n");
	struct sockaddr_in servidor,cliente;
	printf("Puerto:%d \n", port);
	//Paso 1: Creación del socket usando AF_INET
	if (ServS == -1)
	{
		perror("Error al crear el socket");
		exit(EXIT_FAILURE);
	}
	//Paso numero 2 llenamos la estructura del servidor y después publicamos el servicio

	memset(&servidor,0,sizeof(servidor));
	//memset(&servidor,sizeof(servidor), 0);

	//Reinicializando la estructura
	//Puertos no deben de ser menor a 1024 
	//INADDR asigna la interfaz de red por default
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons ( port );
	servidor.sin_addr.s_addr = INADDR_ANY;
/*//incio edit
	int temporal;
	int returnset setsockopt(
		idCanal,
		SOL_SOCKET,
		SO_REUSEADDR,
		&temporal,
		0);*/
//finEdit
	int idBind = bind(ServS,(struct sockaddr*)&servidor
		,sizeof(serviciovidor));
	if (idBind == -1)
	{
		perror("Error en el bind");
		exit(EXIT_FAILURE);
	}

	validarListen = listen(ServS,2);

	if (validarListen == -1 )
	{
		perror("Error al validar listen");
		exit(EXIT_FAILURE);
	}

	int tam = sizeof(cliente);
	idCanal = accept(ServS,(struct sockaddr*)&cliente,&tam); //(struct sockaddr*)&cliente
	//inicio edit
	while(1){
		if (idCanal == -1 )
		{
			printf("Abholen Fehler\n");
		}
	}

	//fin edit
	printf("listen\n");
	if (!idCanal)
	{
		perror("Error en el canal\n");
		exit(EXIT_FAILURE);
	}
	printf("CONFIGURACION COMPLETA\n");
	// Comienza fase de comunicación
	int in,out;
	 while(1)
    {
    	printf("Esperando la respuesta del cliente\n");
        memset(&buffer, 0, sizeof(buffer));//clear the buffer
        in += recv(idCanal, (char*)&buffer, sizeof(buffer), 0);
        if(!strcmp(buffer, "exit"))
        {
        	printf("Fin de la sesión\n");
            break;
        }
        printf("Cliente: %s\n", buffer);
        printf("\n");
        char datos[50];
    	fgets(datos,50,stdin);
        memset(&buffer, 0, sizeof(buffer)); //clear the buffer
        strcpy(buffer, datos);
        if(datos == "exit")
        {
            //send to the client that server has closed the connection
            send(idCanal, (char*)&buffer, strlen(buffer), 0);
            break;
        }
        //send the message to client
        out += send(idCanal, (char*)&buffer, strlen(buffer), 0);
    }

	/*
	int nCar = recv(idCanal,buffer,50,0);
	//buffer[nCar] = '\0';
	bzero(buffer,50);
	printf("Mensaje recibido del cliente: %s\n",buffer);
	strcpy(buffer,'Hola');
	nCar = send(idCanal,buffer,strlen(buffer),0);
	close(ServS);
	*/
	return 0;
}