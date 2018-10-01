#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define N 32
#define NUM_PROC 2



int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimeArreglo(int *datos);
int mayorArreglo(int * datos);
int menorArreglo(int * datos);
void procesoHijo(int np,int *datos);
void procesoPadre();


int main(){

    int *datos;
    datos = reservarMemoria();
    llenarArreglo(datos);
    imprimeArreglo(datos);
    
    int np;
	pid_t pid;
	for(np = 0; np < NUM_PROC; np++)
	{
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso...");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(np,datos);
			
		}
	}
    procesoPadre();
    
    free(datos);
    return 0;
}
void procesoPadre(){
	pid_t pid_hijo;
	printf("Proceso padre ejecutado con pid %d\n",getpid());
	int numero;
	for(int np = 0; np < NUM_PROC; np++){
		pid_hijo = wait(&numero);
		printf("Procesos hijo terminado con pid %d y retorno %d\n",pid_hijo,numero>>8);
	}
		
	exit(0);
}
void procesoHijo(int np,int *datos){
    printf("Procesos hijo %d ejecutado con pid %d \n",np,getpid());
	if(np == 0){
        int mayor = mayorArreglo(datos);
        exit(mayor);
    }else{
        int menor = menorArreglo(datos);
        exit(menor);
    }
}

int mayorArreglo(int * datos){
    register int max = datos[0];
    for(register int i = 0; datos[i]; i++)
    {      
        if (datos[i]>max) {
            max  = datos[i];
        }    
    }
    return max;
}
int menorArreglo(int * datos){
    register int min = datos[0];
    for(register int i = 0; datos[i]; i++)
    {      
        if (datos[i] < min) {
            min  = datos[i];
        }    
    }
    return min;
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
    srand(getpid());
    for( i = 0; i < N; i++)
    {
        datos[i] = rand() % 255;
    }
    
}
void imprimeArreglo(int * datos){
    register int i;
    
    for(i = 0; datos[i]; i++)
    {
        if(!(i%16)){
            printf("\n");
        }
        printf("%5d ",datos[i]);
    }
    printf("\n");
    
}