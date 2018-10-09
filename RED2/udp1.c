#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc,char **argv)
{
	int udpSocket = socket(AF_INET,SOCK_DGRAM,0);
	if(udpSocket == -1)
	{
		perror("Error en el socket");
		EXIT_FAILURE;
	} 
	int puerto = argv[]
	server.sin_family= AF_INET;
	server.sin_addr.s_s_addr= innet_addr(argv[1]);
	server.sin_port = htons(argv[2]);
	//llenado de la estructura del cliente
	server.sin_family= AF_INET;
	servidor.sin_addr.s_addr=INADDR_ANY;
	servidor.sin_port=htons(puerto)
	char *buffer;
}