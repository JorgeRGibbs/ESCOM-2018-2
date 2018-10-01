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

int * reservaMemoria();
void llenarArreglo(int * datos);
void imprimirArreglo(int *datos);
void procesoHijo(int np);
void procesoPadre();
int menorArreglo(int *);
int mayorArreglo(int *);
int promedioArreglo(int *);
int ordenaArreglo(int *);

int main()
{
	int datos[N];
	
	return 0;
}