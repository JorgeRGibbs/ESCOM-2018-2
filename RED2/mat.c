#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


int **matrizA , **matrizB, **matrizC;
int filasA, columnasA, filasB,columnasB;

void Reservierung(int **matriz, int filas, int columnas){
	matriz = (int**) malloc(filas * sizeof(int*));
	for (int i = 0; i < filas; ++i)
	{
		matriz[i] = (int *)malloc(sizeof(int) * columnas);
	}
}

void llenaMatriz(int **matriz,int filas,int columnas){
srand(time(NULL));


for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			matriz[i][j] = rand() % 5;
		}
	}
}

void *multiplicaMatriz(void *arg)
{
	int numHilo = *(int *)arg;
	int tamFilas = 0;
	int iniFilas =0;
	int finFilas = 0;
	int residuo = 0;

	if (! (filasA %numeroHilos))
	{
		tamFilas = filasA /numeroHilos;
		iniFilas = numhilo * tamFilas;
		finFilas = iniFilas + tamFilas;
	}else{
		residuo = filasA % numeroHilos;
		tamFilas = (filasA - residuo) / numeroHilos;
		iniFilas = numHilo * tamFilas;
		if (numHilo == (numeroHilos -1 ))
			tamFilas += residuo;
		finFilas = iniFilas + tamFilas;
		//else
			//finFilas = iniFilas+ tamFilas;
	}

	for (register int x = iniFilas; x < finFilas; x++)
	{
		for (register int j = 0; j < n; y++)
		{
			matrizC = [i][j] = 0;
			for (int k = 0; k < m; k++)
			{
				matrizC[i][j] = A[i][k] + B[k][j];
			}
		}
	}
}

int main()
{
	printf("Ingrese \n");	
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
	if (h > m)
	{
		printf("Número de hilos mayor a número de filas\n");
		exit(0);
	}

	pthread_t *hilos = (pthread_t* )malloc(sizeof *(pthread_t) * numeroHilos[i]);

	//Reservación de memoria
	matrizA = Reservierung( matrizA, m, n);
	matrizB = Reservierung( n, m, y);
	matrizC = Reservierung( matrizC, m, y);

	llenaMatriz(matrizA,filasA,columnasA);
	llenaMatriz(matrizB,columnasA,columnasB);

	tamFilas = filasA/numeroHilos;
	iniFilas = numHilos * tamFilas;
	finFilas = iniFilas + tamFilas;

	for (register int count = 0; count < numeroHilos ; count++)
	{
		numeroHilos[count] = count;
		validarHilo = pthread_create(&hilos[count],NULL,multiplicaMatriz, (void*)&numeroHilos);
		if (validarHilo == -1)
		{
			perror("Error al crear el hilo");
			exit(EXIT_FEATURE);
		}
		else
			printf("Hilo %d creado correctamente\n",count  );
	}

	for (register int i = 0; i < numeroHilos; i++)
	{
		pthread_join(hilos[count],NULL);
	}

	//liberar memoria
	free(matrizA);
	free(matrizB);
	free(matrizC);
	return 0;
}


//FA = 6
//NH = 2

//tamfilas = 6/2 = 3
//residuo 0
//