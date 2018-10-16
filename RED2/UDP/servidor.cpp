
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
    char hola[] = "Hola del servidor"; 
    struct sockaddr_in servaddr, cliaddr; 
      
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
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      

    servaddr.sin_family    = AF_INET;  
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind"); 
        exit(EXIT_FAILURE); 
    } 
      
    unsigned int len, n;
    while(1){ 
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
	if(n<MAXLINE)
    	buffer[n] = '\0'; 
    while(true){
    //printf("Cliente : %s\n", buffer); 
    sendto(sockfd, (const char *)hola, strlen(hola),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len);
        } 
    }
    printf("Mensaje de hola enviado.\n");  
      
    return 0; 
} 