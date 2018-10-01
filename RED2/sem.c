#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void * consumidor(void *);
void * consumidor1(void *);
void * productor(void*);
void * productor1(void*);

char secCrit[2];
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


int main(int argc, char const *argv[])
{
	//creacion de los hilos
	pthread_t hilos[4];

	//int a;

	//a = (void*) malloc (sizeof(pthread_t));
	int prod = pthread_create(&hilos[0],NULL,productor,NULL);
	int cons = pthread_create(&hilos[1],NULL,consumidor,NULL);
	int prod2 = pthread_create(&hilos[2], NULL, productor1, NULL);
	int cons2 = pthread_create(&hilos[3], NULL, consumidor1, NULL);

	if((prod==-1)||(cons==-1)){
		printf("\nError al crear los hilos");
		exit(1);
	}

	pthread_join(hilos[0],NULL);
	pthread_join(hilos[1],NULL);
	pthread_join(hilos[2],NULL);
	pthread_join(hilos[3],NULL);

	semctl(idSem,0,IPC_RMID,0);
	semctl(idSem,1,IPC_RMID,0);
	semctl(idSem,2,IPC_RMID,0);
	semctl(idSem,3,IPC_RMID,0);

	
}

void * consumidor(void * arg){
	key_t key = ftok("/bin/ls",'b');
	idSem =semget(key,4,0666 | IPC_CREAT | IPC_EXCL);
	if(idSem==-1){
		idSem = semget(key,4,0666);
		if(idSem==-1){
			printf("\nError en ligarse");
			exit(1);
		}
	else{
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,0);
		semctl(idSem,3,SETVAL,0);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		cierre(1);
		printf("\nConsumidor %d: %c\n",i, secCrit[0]);
		apertura(0);
	}
}

void * productor(void *arg){
//creacion de la llave 
	key_t key = ftok("/bin/ls",'b');
	//paso 1: creación del mec de sincronización
	idSem =  semget(key,4,0666 | IPC_CREAT | IPC_EXCL); //tarea //semget va a regresar el id del semáforo.
	//solamente una vez se debe crear e inicializar el mecanismo de sincronizacion.
	if (idSem == -1)
	{
		idSem  =  semget(key,4,0666); //tarea //semget va a regresar el id del semáforo.
		if (idSem == -1)
		{
			printf("error al ligarse al semáforo");
			exit(1);
		}
	}else{
		//inicializando al semaforo 
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,0);
		semctl(idSem,3,SETVAL,0);
	}
	for (int i = 0; i < 20; i++)
	{
		cierre(0);
		secCrit[0] = 'a';
		printf("\nProductor %d: %c\n",i, secCrit[0]);
		apertura(1);
	}

}

void * consumidor1(void * arg){
	key_t key = ftok("/bin/ls",'b');
	idSem =semget(key,4,0666 | IPC_CREAT | IPC_EXCL);
	if(idSem==-1){
		idSem = semget(key,4,0666);
		if(idSem==-1){
			printf("\nError en ligarse");
			exit(1);
		}
	else{
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,0);
		semctl(idSem,3,SETVAL,0);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		cierre(3);
		printf("\nConsumidor %d: %c\n",i, secCrit[1]);
		apertura(0);
	}
}

void * productor1(void *arg){
//creacion de la llave 
	key_t key = ftok("/bin/ls",'b');
	//paso 1: creación del mec de sincronización
	idSem =  semget(key,4,0666 | IPC_CREAT | IPC_EXCL); //tarea //semget va a regresar el id del semáforo.
	//solamente una vez se debe crear e inicializar el mecanismo de sincronizacion.
	if (idSem == -1)
	{
		idSem  =  semget(key,4,0666); //tarea //semget va a regresar el id del semáforo.
		if (idSem == -1)
		{
			printf("error al ligarse al semáforo");
			exit(1);
		}
	}else{
		//inicializando al semaforo 
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,0i);
		semctl(idSem,3,SETVAL,0);
	}
	for (int i = 0; i < 20; i++)
	{
		cierre(2);
		secCrit[1] = 'b';
		printf("\nProductor %d: %c\n",i, secCrit[1]);
		apertura(3);
	}

}