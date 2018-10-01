/*
--------------
procesos.c
procesohijo
procesopadre
--------------
*/
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

void procesoPadre()
{
	//sleep(5);
	int np;
	int numero;
	pid_t pid_hijo;
	printf("Proceso padre ejecutado con pid %d\n",getpid() );
	for (np = 0; np < NUM_PROC ; np++)
	{
		pid_hijo = wait(&numero);
		printf("Proceso hijo con pid %d y retorno %d\n",pid_hijo, numero>>8);
	}
}

void procesoHijo(int np, int *datos)
{		int mayor, menor;
		int prom;
		printf("Proceso hijo %d con pid %d\n",np, getpid());
	//	while(1);	
		if( np == 0 )
		{
			//printf("Proceso %d\n",np);
			mayor = mayorArreglo(datos);
			printf("El número mayor es: %d\n",mayor);
			exit(mayor);
		}else if (np == 1)
		{
			//printf("Proceso %d\n",np);
			menor = menorArreglo(datos);
			printf("El número menor es: %d\n",menor);
			exit(menor);
		}else if(np== 2)
		{
			//printf("Proceso %d\n",np);
			prom = promedioArreglo(datos);
			printf("El promedio es: %d\n",prom);
			exit(prom);
		}else if (np ==3)
		{
			//printf("Proceso %d\n",np);
			ordenaArreglo(datos);
			imprimirArreglo(datos);
			exit(*datos);
		}

		exit(np);
}
	

