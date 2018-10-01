#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void * myFunction( void* );

int main(){
	
	int cantidad;
	int x = 5;
	int f;
	int i = 0;
	pthread_t *firstThread;
	char *respuesta;
	int *numero;
	
	printf("Ingresa la cantidad de hilos: ");
	scanf("%d",&cantidad);
	firstThread = (pthread_t*) malloc(cantidad*sizeof(pthread_t));
	numero = (int *) malloc(cantidad*sizeof(int));
	
	for(i = 0; i < cantidad; i++){
		numero[i] = i;
		f = pthread_create(&firstThread[i],NULL,myFunction,&numero[i]);
		printf("El padre creo al hilo: %p \n",&firstThread[i]);
		
		if(f == -1){
			
			printf("Error al crear el hilo");
			exit(0);
			
		}
			
	}
	
	for(i = 0; i < cantidad; i++){
		
		pthread_join(firstThread[i],(void **)&respuesta);
		printf("Escribiendo desde el padre la cadena del hilo enviada: %s \n",respuesta);
		
	}
			
	return 0;
}

void *myFunction(void *a){
	
	char *as;
	as = malloc(4*sizeof(char));
	strcpy(as,"hijo");

	pthread_exit(as);
}
