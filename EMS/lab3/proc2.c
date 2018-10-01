#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#define NUM_PROC 4

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
	int status;
	int pid_hijo;
	printf("Proceso padre ejecutado con pid %d\n",getpid() );
	for (np = 0; np < NUM_PROC ; np++)
	{
		pid_hijo = wait(&status);
		printf("proceso hijo %d terminado con pid %d\n",status>>8, pid_hijo);
	}
}

void procesoHijo(int np)
{
		printf("Proceso hijo %d con pid %d\n",np, getpid());
		while(1);	
		exit(np);
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