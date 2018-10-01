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

void llenarArreglo(int *datos)
{
	srand(time(NULL));
	register int i;
	for (i = 0; i < N; i++)
	{
		datos[i] = rand() % 255;
	}
	printf("Arreglo en desorden:\n");
	for (int i = 0; i < N; i++)
	{
		printf("número %d: %d\n", i, datos[i]);
	} 
}

void imprimirArreglo(int * datos,int mayor,int menor,int prom){
	//int mayor,menor;
	register int i;
	/*printf("Arreglo en desorden:\n");
	for (int i = 0; i < N; i++)
	{
		printf("número %d: %d\n", i, datos[i]);
	} */	
	//printf("El número mayor es: %d\n",mayor);
	//printf("El número menor es: %d\n",menor);
	//printf("El promedio es: %d \n",prom );
	printf("Arreglo ordenado: \n");
	for (i = 0; i < N ; i++)
	{
		printf("Dato %d : %d\n",i,datos[i] );
	}

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
