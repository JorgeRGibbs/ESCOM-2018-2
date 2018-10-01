#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include "defs.h"

/*
4 módulos
datos.c
reservarMemoria
imprimeMemoria
llenarArreglo
*/

int * reservaMemoria();
void llenarArreglo(int * datos);
void imprimirArreglo(int *datos);

int main()
{
	int *datos;
	imprimirArreglo(datos);
}

void llenarArreglo(int *datos)
{
	srand(time(NULL));
	register int i;
	for (i = 0; i < N; i++)
	{
		datos[i] = rand() % 255;
	}
}

void imprimirArreglo(int * datos){
	//int mayor,menor;
	register int i;
	datos = reservaMemoria();
	llenarArreglo(datos);
	/*for (int i = 0; i < N ; i++)
	{
		printf("dato %d : %d\n",i,datos[i] );
	}*/
	//imprimirArreglo(datos);
	//mayor = mayorArreglo(datos);
	//menor = menorArreglo(datos);

	//printf("El numero mayor es: %d\n",mayor);
	//printf("El numero mayor es: %d\n",menor);

	free(datos);
	printf("Memoria liberada\n");
}

int * reservaMemoria()
{
	int *mem;
	mem = (int *) malloc(N * sizeof(int ));
	printf("Memoria reservada en %p \n", &mem);
	if (!mem)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	return mem;
}
