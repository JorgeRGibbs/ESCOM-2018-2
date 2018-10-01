#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//Estructura con int, float, y un apuntador para la cadena
struct ejemplo{
	int identificador;
	float flotante;
	char *cadena;
};

//Método que devuelve un apuntador a la estuctura
struct ejemplo *funcion(struct ejemplo *parametro){
	printf("Soy el hijo con\n");
	printf("\tCadena = 		%s\n",parametro -> cadena);
	printf("\tFlotante = 		%f\n",parametro -> flotante);
	printf("\tIdentificador = 	%d\n",parametro -> identificador);
	parametro -> cadena = "read";
	return parametro; //Nota devuelves un apuntador
}

int main(){
	pthread_t *listaDeHilos;
	int i, numeroDeHilos,*retornoCreate;
	struct ejemplo *listaParametros, **listaRetorno;
	while(1){
		printf("Inserte el num de hilos (0 para Salir) :");
		scanf("%d",&numeroDeHilos);
		if(numeroDeHilos == 0)
			break;
		listaDeHilos 	= malloc(sizeof(pthread_t) * numeroDeHilos);
		listaParametros = malloc(sizeof(struct ejemplo) * numeroDeHilos);
		retornoCreate 	= malloc(sizeof(int) * numeroDeHilos);

		for(i=0; i<numeroDeHilos; i++){
			listaParametros[i].cadena = malloc(sizeof(char) * 5); //Almacenas la memoria para la cadena
			listaParametros[i].cadena = "hola"; 
			listaParametros[i].identificador = i;
			listaParametros[i].flotante = (float)i/5;
			retornoCreate[i]=pthread_create(listaDeHilos + i, NULL, funcion, listaParametros + i);
			printf("Naciste hijo %d\n",i);
		}
		listaRetorno = malloc(sizeof(struct ejemplo)*numeroDeHilos);
		
		for(i=0; i<numeroDeHilos; i++){
			pthread_join(listaDeHilos[i],listaRetorno+i);
			printf("Mi hijo a hablado %s\n",listaRetorno[i] -> cadena);
			printf("\t se modifico el original? %s\n",listaParametros[i].cadena);
		}
			
		free(listaDeHilos);
		free(listaParametros);
		free(listaRetorno);
		printf("Ya tengo espacio\n");
	}
	printf("THE END\n");
	return 0;
}


