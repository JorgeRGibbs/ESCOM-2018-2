#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
  int idSocket,port,bindVal;
  struct sockaddr_in servidor, cliente;
  char *buffer = malloc(sizeof(char)*(strlen(buffer)+1));
  port = atoi(argv[1]);
  idSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if(idSocket==-1)
  {
    perror("Error al crear el socket\n");
    exit(EXIT_FAILURE);
  }
  memset(&servidor,0,sizeof(servidor));
  memset(&cliente,0,sizeof(cliente));

  servidor.sin_family=AF_INET;
  servidor.sin_port=htons(port);
  servidor.sin_addr.s_addr=INADDR_ANY;
  //memset(servidor.sin_zero,'\0',sizeof servidor.sin_zero);  

  printf("Port: %d\n",port );
  bindVal=bind(idSocket,(struct sockaddr *)&servidor, sizeof(servidor));
  if(bindVal==-1)
  {
    perror("Error en el Bind\n");
    exit(EXIT_FAILURE);
  }
  printf("CONFIGURACION COMPLETA\n");

  socklen_t clienteTam;
  int a = recvfrom(idSocket,
          (char*)buffer, 
          100, 
          MSG_WAITALL,
          (struct sockaddr *)&cliente, 
          &clienteTam);
  buffer[a] = '\0';
  char *ipCliente;
  //memcpy(ipCliente,&cliente.sin_addr.s_addr,sizeof(cliente.sin_addr.s_addr));
  printf("Mensaje del cliente :%s",buffer);
  char *respuesta="Hola ClienteUDP";
  while(1){
  sendto(idSocket,
         (const char*)respuesta,
         strlen(respuesta),
         MSG_CONFIRM,
         (const struct sockaddr *)&cliente
         ,clienteTam);
  printf("respuesta enviada\n");
  //close(idSocket);
  }
}
  