#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_PROC 4
#define N 32


int * reservaMemoria();
void llenarArreglo(int * datos);
void  imprimirArreglo();
int menorArreglo(int *);
int mayorArreglo(int *);


int main(){
	int *datos;
	datos = reservaMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	return 0;
}


int * reservaMemoria()
{
	int *mem;
	mem = (int *) malloc(N * sizeof(int ));
	if (!mem)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	return mem;
}

void llenarArreglo(int * datos){
	register int i;
	srand(getpid());
	for(i=0;i<NUM_PROC;i++){
		datos[i] = rand()%255;
	}
}

void imprimirArreglo(int * datos){
	int mayor,menor;
	register int i;
	datos = reservaMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	mayor = mayorArreglo(datos);
	menor = menorArreglo(datos);

	printf("El numero mayor es: %d\n",mayor);
	printf("El numero mayor es: %d\n",menor);


	free(datos);
}


int menorArreglo (int *datos)
{
	register int i, menor;
	
	menor  = datos[0];
	
	for (int i = 0; i < NUM_PROC; i++)
	{
		if (datos [i] < menor)
		{
			menor = datos[i];
		}
	}
	return menor;
}

int mayorArreglo (int *datos)
{
	register int i, mayor;
	mayor  = datos[0];
	for (int i = 0; i < NUM_PROC; i++)
	{
		if (datos [i] > mayor)
		{
			mayor = datos[i];
		}
	}
}