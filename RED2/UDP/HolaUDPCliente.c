#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include <arpa/inet.h>

int main(int argc,char **argv)
{
  int idSocket,port;
  struct sockaddr_in servidor;
  char buffer[100];
  port = atoi(argv[1]); 
  idSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if(idSocket==-1)
  {
    printf("Error al crear el socket\n");
    EXIT_FAILURE;
  }
  memset(&servidor,0,sizeof(servidor));
  servidor.sin_family=AF_INET;
  servidor.sin_port=htons(port);
  servidor.sin_addr.s_addr=INADDR_ANY;
  //llenamos estructura del cliente
  /*
  memset(&cliente,0,sizeof(cliente));
  cliente.sin_family=AF_INET;
  cliente.sin_addr.s_addr=INADDR_ANY;
  cliente.sin_port=htons(port);
  //memset(servidor.sin_zero,'\0',sizeof servidor.sin_zero);
  */

  /*bindVal=bind(idSocket,(struct sockaddr*)&cliente, sizeof(cliente));
  if(bindVal==-1)
  {
    printf("Error en el Bind\n");
    EXIT_FAILURE;
  }*/
  printf("CONFIGURACION COMPLETA\n");

  int servidorTam;
  char *mensaje="Hola ServidorUDP\n";
  //socklen_t len = sizeof(servidor); 
  sendto(idSocket,
        (const char*)mensaje,
         strlen(mensaje),
         MSG_CONFIRM ,
         (const struct sockaddr *)&servidor,
         sizeof(servidor));
  printf("Mensaje enviado!\n");
  int a = recvfrom(
    idSocket,
    (char*)buffer,
    100,
    MSG_WAITALL,
    (struct sockaddr *)&servidor,
    0);
  //buffer = malloc(sizeof(char)*strlen(buffer));
  //char *ipServidor=memcpy(servidor.sin_addr.s_addr);
  if (a == -1)
  {
    perror("Error recibiendo el mensaje");
    exit(EXIT_FAILURE);
  }
  buffer[a] = '\0';
  printf("Mensaje del servidor:%s",buffer);
  close(idSocket);

  return 0;
}
