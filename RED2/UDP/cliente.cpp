
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define MAXLINE 1024 
  
 
int main(int argc, char const *argv[]) { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char hola[] = "Hola del cliente"; 
    struct sockaddr_in     servaddr; 
  	int PORT;
	
	if(argc<=1){
		printf("Argumento faltante: puerto.\n");
		exit(-1);
	}
	
	PORT = atoi(argv[1]);
 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    unsigned int n;
    socklen_t len = (socklen_t) sizeof servaddr; 
    while(1){
    sendto(sockfd, (const char *)hola, strlen(hola), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    //printf("Mensaje de hola enviado.\n"); 
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len);
	if(n<MAXLINE)
    	buffer[n] = '\0'; 
    printf("Servidor : %s\n", buffer); 
    }
    close(sockfd); 
    return 0; 
} 