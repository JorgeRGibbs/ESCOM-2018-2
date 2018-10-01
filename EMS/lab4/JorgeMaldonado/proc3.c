#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define N 32


void procesoHijo(int np);
void procesoPadre();
int * reservarMemoria();
void llenarArreglo();

int main(){
    int *datos;
    datos = reservarMemoria();
    llenarArreglo(datos);
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

int * reservarMemoria(){
    int * memoria;
    memoria = (int*)malloc(sizeof(int)*N);
    if(!memoria){
        perror("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    return memoria;
}

void llenarArreglo(int *datos){
    register int i;
    for( i = 0; i < N; i++)
    {
        datos[i] = rand() % 255;
    }
    
}