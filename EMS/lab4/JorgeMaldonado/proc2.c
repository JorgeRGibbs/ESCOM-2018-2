#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define NUM_PROC 4


void procesoHijo(int np);
void procesoPadre();
int main(){

	pid_t pid;
	printf("Probando procesos...");
	int np;
	
	for(np = 0; np < NUM_PROC; np++)
	{
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso...");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(np);
			exit(0);
		}else{
			
		}
	}
	procesoPadre();
	
	return 0;
}
void procesoPadre(){
	pid_t pid_hijo;
	printf("Proceso padre ejecutado con pid %d\n",getpid());
	int estado;
	for(int np = 0; np < NUM_PROC; np++){
		pid_hijo = wait(&estado);
		printf("Procesos hijo %d terminado con pid %d\n",estado>>8,pid_hijo);
	}
		
	exit(0);
}
void procesoHijo(int np){
	printf("Procesos hijo %d ejecutado con pid %d\n",np,getpid());
	
	while(1);
	exit(np);
}