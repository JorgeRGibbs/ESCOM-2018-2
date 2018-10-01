
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>

#define N 32

int * reservarmemoria();
void llenararreglo(int * datos);
void imprimirarreglo();
void imprimirarreglo(int *datos);
int menorArreglo(int *datos);
int mayorArreglo(int *datos);



int main(int argc, char const *argv[])
{

	int *datos,mayor,menor;
	datos=reservarmemoria();
	llenararreglo(datos);
	imprimirarreglo(datos);
	
	mayor=mayorArreglo(datos);
	menor=menorArreglo(datos);
	
	printf("El numero mayor :%d\n", mayor);
	printf("El numero menor :%d\n", menor);

	free(datos);


	return 0;


}

int mayorArreglo(int *datos)
{
	register int i,mayor;
	mayor=datos[0];
	for (i = 1; i < N; i++)
	{	
		if(datos[i]> mayor)
			mayor=datos[i];
	}
	return mayor;
}

int menorArreglo(int *datos)
{
	register int i,menor;
	menor=datos[0];
	for (i = 1; i < N; i++)
	{	
		if(datos[i]<menor)
			menor=datos[i];
	}
	return menor;
}


void imprimirarreglo(int *datos)
{
	register int i;
	for (i = 0; i < N; i++)
	{
		if(!(i%16))
		{
			printf("\n");
		}
		printf("%3d ", datos[i]);

	}
	printf("\n\n");
}


void llenararreglo(int *datos)
{
	register int i;
	srand(getpid());
	for ( i = 0; i <N; i++)
	{
		datos[i]=rand()%255;
	}
}


int * reservarmemoria()
{

	int *mem;
	mem=(int *) malloc(sizeof(int) * N);
	if( !mem)
	{
		perror("Error al asignar memoria ... \n");
		exit(EXIT_FAILURE);
	}
	return mem;


}