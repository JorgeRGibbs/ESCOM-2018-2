#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* myFunction(void* a){
	printf("Hallo Welt\n");
	pthread_exit(NULL);
}

int main()
{
	/*Paso 1: Creación del hilo*/
	int a;
	pthread_t firstThread;
	int f;
	int x = 5;
	
	f = pthread_create(&firstThread,NULL,myFunction,/*(void*)*/&myFunction);

	if (f == -1)
	{
		printf("Fehler\n");
		exit(1);
	}

	pthread_join(firstThread, NULL);
	return 0;	
}
