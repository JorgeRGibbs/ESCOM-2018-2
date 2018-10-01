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

void procesoHijo(int np);
void procesoPadre();

int main()
{
	int status;
	int pid_hijo;
	int np;
	float num1 = 23, num2 = 12, suma, resta;
	pid_t pid;
	printf("Probando procesos...\n");
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
			procesoHijo(np);
		}
	}
	procesoPadre();

	return 0;
}

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
		printf("proceso hijo con pid %d y retorno %d\n",pid_hijo, numero>>8);
	}
}

void procesoHijo(int np)
{		int mayor, menor,prom;
		printf("Proceso hijo %d con pid %d\n",np, getpid());
	//	while(1);	
		if( np == 0 )
		{
			mayor = mayorArreglo(datos);
			exit(mayor);
		}else if (np == 1)
		{
			menor = menorArreglo(datos);
			exit(menor);
		}else if(np== 2)
		{
			prom = promedioArreglo(datos);
			exit(prom);
		}else if (np ==3)
		{
			ordenaArreglo(datos);
			imprimirArreglo(datos);
			exit(np);
		}

		exit(np);
}


