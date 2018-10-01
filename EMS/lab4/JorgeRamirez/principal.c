/*principal.c
main()*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include "defs.h"
#include "datos.h"
#include "procesamiento.h"
#include "procesos.h"

/*int * reservaMemoria();
void llenarArreglo(int * datos);
void imprimirArreglo(int *datos);
void procesoHijo(int np);
void procesoPadre();
int menorArreglo(int *);
int mayorArreglo(int *);
int promedioArreglo(int *);
int ordenaArreglo(int *);*/

int main()
{
	int *datos;
	int status;
	int pid_hijo;
	int np;
	pid_t pid;
	datos = reservaMemoria();
	llenarArreglo(datos);
	
	for (int np = 0; np < NUM_PROC; np++)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Fehler! \n");
			exit(EXIT_FAILURE);
		}
		if (!pid)
		{
			procesoHijo(np,datos);
		}
	}
	procesoPadre();

	return 0;
}