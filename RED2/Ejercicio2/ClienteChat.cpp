#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>



int main( int argc, char const *argv[] ){
	
	int idSocket,puerto,idCanal,caracteresRecibidos,enviado,conexion;
	struct sockaddr_in servidor;
	char buffer[50];
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
	
	if(connect(idSocket,(struct sockaddr *)&servidor,sizeof(servidor))==-1){
		perror("Error al realizar el Connect");
		exit(EXIT_FAILURE);		
	}
	
	
	while(buffer[0]!='@'){
		char mensaje[50];
		printf("Tu mensaje: ");
		fgets(mensaje,50,stdin);
		enviado = send(idSocket,mensaje,strlen(mensaje),0);
	
		caracteresRecibidos = recv(idSocket,buffer,50,0);
		buffer[caracteresRecibidos] = '\0';
		printf("Servidor: %s \n",buffer);

	}
	
		
	close(idSocket);
	
	return 0;
}