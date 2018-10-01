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
	/*Paso 1: Creación del hilo*/
	int a;
	pthread_t firstThread[10];
	int f;
	int x = 10;
	
	for (int i = 0; i < 10 ; i++)
	{
		f = pthread_create(&firstThread[i],NULL,myFunction,/*(void*)*/&firstThread[i]);
		printf("El padre creó al hilo: %p\n",firstThread );
		if (f == -1)
		{
			printf("Fehler!\n");
			exit(1);
		}
	}

	for (int i = 0; i < x; i++)
	{
		pthread_join(firstThread[i], NULL);
	}
	return 0;	
}
