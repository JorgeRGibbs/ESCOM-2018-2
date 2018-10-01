#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



void* myFunction(void* a){

	pthread_t* b = (pthread_t *) a;
	printf("Hallo Welt: %p\n", a);
	pthread_exit(NULL);
}

int main()
{
	int x;
	printf("Ingrese el número de hilos\n");
	scanf("%d",&x);
	pthread_t*firstThread = (pthread_t*)malloc(x*sizeof(pthread_t)); 
	int a;
	int f;	
	/*Paso 1: Creación del hilo*/
	
	for (int i = 0; i < x ; i++)
	{
		f = pthread_create(firstThread,NULL,myFunction,/*(void*)*/&firstThread);
		printf("El padre creó al hilo: %p\n",firstThread );
		if (f == -1)
		{
			printf("Fehler!\n");
			exit(1);
		}
	}

	for (int i = 0; i < x; i++)
	{
		pthread_join(*firstThread, NULL);
	}
		free(firstThread);
	return 0;	
}
