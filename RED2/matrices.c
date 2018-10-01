#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

struct est{
	int m,n,x;
};
struct est *f(struct est *pass)
{
	m  = pass -> m;
	n  = pass -> n;
	x  = pass -> x;

	//Multiplicación de matrices

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < m; k++)
			{
				C[i][j] = A[i][k] + B[k][j];
			}
		}
	}


	return pass;
}

int main()
{
	int m,n,x,y,h,t;
	srand(time(NULL));
	printf("Generar matriz A de\n");
	scanf("%d",&m);
	printf("\npor\n");
	scanf("%d",&n);
	printf("\ncolumnas\n");
	y = m;
	printf("\n");
	printf("Generar matriz B de\n");
	scanf("%d",&x);
	printf("\npor\n");
	printf("%d\n",y);
	printf("\ncolumnas\n");
	printf("\n");
	printf("¿Cúantos hilos?\n");
	scanf("%d",&h);

	/*Reservación de memoria de los hilos*/

	pthread_t *hilos = (pthread_t*)malloc(h*sizeof(pthread_t));
	int *pass = (int*)malloc(h*sizeof(pthread_t));

	if ( h > m)
	{
		printf("hilos mayores a filas\n");
		exit(0);
	}

	// Reservación de memoria para ambas matrices.
	int **A = (int **)malloc(m*sizeof(int *));
	int ** B = (int **)malloc(x*sizeof(int*));
	for (int i = 0; i < m; i++)
	{
		A[i] = (int *)malloc( n * sizeof(int));
	}


	for (int i = 0; i < x; i++)
	{
		B[i] = (int*)malloc(y * sizeof(int));
	}

	//Reservación de memoria para matriz C

	int ** C = (int **)malloc(x*sizeof(int*));

	for (int i = 0; i < x; i++)
	{
		C[i] = (int *)malloc(n * sizeof(int));
	}
	
	//Llenado de matriz A
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = rand() % 5;
		}
	}

	//Llenado de matriz B

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			B[i][j] = rand() % 4;
		}
	}

	
	//Mostrar matrices
	printf("\nMatriz A\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("[%d][%d]:%d\n",i,j,A[i][j]);
		}
	}

	printf("\nMatriz B\n");
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			printf("[%d][%d]:%d\n",i,j,B[i][j]);
		}
	}

	printf("\nREALIZANDO MULTIPLICACIÓN\n");

	for (int i = 0; i < num; ++i)
	{
		t = pthread_create(hilos[i],NULL,f, est[i]);
	}

	//Mostrar C
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("[%d][%d]:%d\n",i,j,C[i][j]);	
		}
	}

	for (int i = 0; i < num; ++i)
	{
		pthread_join(hilos[i],datos[i]);
	}
}