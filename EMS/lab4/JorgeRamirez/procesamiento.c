/*---------------
procesamiento.c
mayorArreglo
menorArreglo
promerdioArreglo
ordenaArreglo
---------------*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include "datos.h"
#include "defs.h"


int promedioArreglo(int *datos)
{
	register int i;
	int prom,aux,sum;
	for (i = 0; i < N ; i++)
	{
		aux = datos[i];
//		printf("aux: %d\n",datos[i] );
		sum= sum + aux;
		fflush(stdout);
	}

	prom = sum/N;
	return prom;
}

int ordenaArreglo(int *datos)
{	
	register int i;
	int d,t;
	for (i = 1 ; i <= N - 1; i++) {
    	d = i;
    	while ( d > 0 && datos[d-1] > datos[d]) {
    		t          = datos[d];
      		datos[d]   = datos[d-1];
      		datos[d-1] = t;
 			d--;
    	}
  	}
 	/*printf("Arreglo ordenado\n");
  	for (i = 0; i <= N - 1; i++) {
    	printf("Dato %d : %d\n", i,datos[i]);
  }*/
  return *datos;
 
}

int menorArreglo (int *datos)
{
	register int i, menor;
	
	menor  = datos[0];

	for ( i = 0; i < N; i++)
	{
		if (datos [i] < menor)
		{
			menor = datos[i];
		}
	}
	//printf("menor: %d\n", menor);
	return menor;
}

int mayorArreglo (int *datos)
{
	register int i, mayor;
	mayor  = datos[0];

	for (i = 0; i < N; i++)
	{
		if (datos [i] > mayor)
		{
			mayor = datos[i];
		}
	}
	//printf("mayor: %d\n",mayor);
	return mayor;
}
