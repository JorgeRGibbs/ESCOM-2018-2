#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#define NUM_PROC 4

int * reservaMemoria(int n);
int llenarArreglo( int *datos);

int main()
{
	int *datos;
	datos = reservaMemoria();
	llenarArreglo(datos);
	return 0;
}
//Funcion para reservar memoria (No shit)
int * reservaMemoria(int n)
{
	int *mem;
	mem = (int *) malloc(n * sizeof(int ));
	if (!mem)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	return mem;
}

void llenarArreglo(int *datos)
{
	srand(time(NULL));
	register int i;
	for (i = 0; i < n; i++)
	{
		datos[i] = rand() % 255;
	}
}