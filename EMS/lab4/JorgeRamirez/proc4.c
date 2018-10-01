#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define NUM_PROC 4
#define N 32

void procesoHijo(int np, int menor, int mayor);
void procesoPadre();
int * reservaMemoria();
void llenarArreglo(int * datos);
void imprimirArreglo(*datos);
int menorArreglo(int *);
int mayorArreglo(int *);


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

void procesoHijo(int np, int menor,int mayor)
{		int mayor, menor;
		printf("Proceso hijo %d con pid %d\n",np, getpid());
	//	while(1);	
		if( np == 0 )
		{
			mayor = mayorArreglo(datos);
			exit(mayor);
		}else if (np == 1)
		{
			menor = menorArreglo(datos);
			exiit(menor);
		}else if(np== 2)
		{
			promedio = promedioArreglo(datos);
			exit(promedio);
		}else if (np ==3)
		{
			ordenaArreglo(datos);
			imprimirArreglo(datos);
			exit(np);
		}

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


int * reservaMemoria(int n)
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

//ordenar datos y buscar promedio, usar dos procesos
//hausarbeite
/*
4 módulos
datos.c
reservarMemoria
imprimeMemoria
llenarArreglo
---------------
procesamiento.c
mayorArreglo
menorArreglo
promerdioArreglo
ordenaArreglo
--------------
procesos.c
procesohijo
procesopadre
--------------
principal.c
main()
*/