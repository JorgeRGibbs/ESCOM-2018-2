#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#define NUM_PROC 2
#define N 32



void procesoHIJO(int np,int *datos);
void procesoPadre();

int * reservarmemoria();
void llenararreglo(int * datos);
void imprimirarreglo();
void imprimirarreglo(int *datos);
int menorArreglo(int *datos);
int mayorArreglo(int *datos);



int main(int argc, char const *argv[])
{
	printf("Probando procesos ...\n");
	pid_t pid;
	int np, *datos,mayor,menor;
	datos=reservarmemoria();
	llenararreglo(datos);
	imprimirarreglo(datos);
	for( np=0;np <NUM_PROC;np++)
	{
		pid=fork();
			if(pid == -1)
			{
				perror("No se creo el procesos .. \n");
				exit(EXIT_FAILURE);
			}
			if( ! pid )
			{
				procesoHIJO(np,datos);
			}
		
			
			
	}
	procesoPadre(np);
	return 0;


}

void procesoPadre()
{
			int np,numero;
			pid_t pid_hijo;
			printf("Proceso padre ejecutando con pid %d\n", getpid());
			for (np= 0; np < NUM_PROC; np++)
			{
				

				pid_hijo=wait(&numero);
				printf("procesos hijo termino con pid %d  y retorno %d .\n",pid_hijo,numero>>8);




			}



}

void procesoHIJO(int np,int *datos)
{
	printf("procesos HIJO %d ejecutando con pid  %d\n",np,getpid());
//	while(1);
	int mayor,menor,promedio;
	if(np == 0)
	{
		mayor=mayorArreglo(datos);
		exit( mayor );
	}
	else if(np == 1)
	{
		menor=menorArreglo(datos);
		exit( menor );
	}
	// else if(np== 2)
	// {
	// 	//HACER EL PROMEDIO
	// 	promedio=promedioArreglo( datos);
	// 	exit(np);
	// }
	// else if (np == 3)
	// {
	// 	//HACER EL ORDENAMIENTO DE EL ARREGLO
	// 	promedio=ordenarArreglo( datos);
	// 	imprimirarreglo( datos );
	// 	exit(np);

	// }


	
	
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






/*
Al final los archivos deben de quedar 

datos.c
reservarmemoria.c
imprimirarreglo.c
llenararreglo.c
procesamiento.c
mayorarreglo.c
menorarreglo.c
promedioarreglo.c
ordenararreglo.c
procesos.c
procesosHijo
procesosPadre
principal.c
main()






*/