#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void * consumidor(void*);
void * productor(void*);
int secCrit;
int idSem;


void cierre(int numSem){
	struct sembuf sops;
	sops.sem_num=numSem;//numero del semaforo
	sops.sem_op=-1;//operacion
	sops.sem_flg=SEM_UNDO;//máscara de bits
	semop(idSem,&sops,1);//nsops es el numero de operaciones	
}


void apertura(int numSem){
	struct sembuf sops;
	sops.sem_num=numSem;//numero del semaforo
	sops.sem_op=1;//operacion
	sops.sem_flg=SEM_UNDO;//máscara de bits
	semop(idSem,&sops,1);//nsops es el numero de operaciones	
}



int main(){

pthread_t hilos[2];

int prod = pthread_create(&hilos[0], NULL, productor, NULL);
int cons = pthread_create(&hilos[1], NULL, consumidor, NULL);

if((prod==-1)||(cons==-1)){
	printf("\nError al crear los hilos");
	exit(1);
}

pthread_join(hilos[0],NULL);
pthread_join(hilos[1],NULL);

semctl(idSem,0,IPC_RMID,0);
semctl(idSem,1,IPC_RMID,0);

}

void * productor(void* cosa1){
	//paso 0:creación de la llave
	key_t key =ftok("/bin/ls",'b');//path  a un archivo
	//paso1:creación del mec de sincronización
	idSem = semget(key,2,0666 | IPC_CREAT | IPC_EXCL);//tarea
	if(idSem==-1){
		//ligado al semáforo
		idSem = semget(key,2,0666);	
		if(idSem==-1){
			printf("\nError en ligarse");
			exit(1);
		}
	}
	else{
		//inicialización del semáforo
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
}
	for(int i=0;i<20;i++){//producciones en la sección crítica
		cierre(0);
		printf("\nProduce: %d \n",i);
		secCrit=i;
		apertura(1);
	}

//solamente una vez se debe crear e inicializar el mecanismo de sincronización
}

void * consumidor(void * cosa2){
	key_t key = ftok("/bin/ls",'b');
	idSem =semget(key,2,0666 | IPC_CREAT | IPC_EXCL);
	if(idSem==-1){
		idSem = semget(key,2,0666);
		if(idSem==-1){
			printf("\nError en ligarse");
			exit(1);
		}
	else{
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
	}
}
	for(int i=0;i<20;i++){//consumos en la sección crítica
		cierre(1);
		printf("\nconsumos: %d\n",secCrit);
		apertura(0);
	}

}

//tarea buscar tipos de errores de semget




