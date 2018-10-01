#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void * consumidor(void *);
void * productor(void *);

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
	int flags[2];
	//int a;

	//a = (void*) malloc (sizeof(pthread_t));
	int prod =  pthread_create(&hilos[0], NULL, productor,1);
	int prod2 = pthread_create(&hilos[1], NULL, productor, 2);
	int prod3 = pthread_create(&hilos[2], NULL, productor, 3);
	int cons =  pthread_create(&hilos[3], NULL, consumidor,1);
	int cons2 = pthread_create(&hilos[4], NULL, consumidor, 2);

	if((prod==-1)||(cons==-1)){
		printf("\nError al crear los hilos");
		exit(1);
	}

	pthread_join(hilos[0],NULL);
	pthread_join(hilos[1],NULL);
	pthread_join(hilos[2],NULL);
	pthread_join(hilos[3],NULL);
	pthread_join(hilos[4],NULL);

	semctl(idSem,0,IPC_RMID,0);
	semctl(idSem,1,IPC_RMID,0);
	semctl(idSem,2,IPC_RMID,0);
	semctl(idSem,3,IPC_RMID,0);

	
}

void * consumidor(void * arg){
	key_t key = ftok("/bin/ls",'b');
	idSem =semget(key,4,0666 | IPC_CREAT | IPC_EXCL);
	if(idSem==-1){
		idSem = semget(key,4,0666)
		if(idSem==-1){
			printf("\nError en ligarse");
			exit(1);
		}
	else{
		semctl(idSem,0,SETVAL,2);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,1);
		semctl(idSem,3,SETVAL,1);
		semctl(idSem,4,SETVAL,0);
		semctl(idSem,5,SETVAL,0);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		cierre(1);
		printf("\nConsumidor %d: %c\n",i, secCrit[0]);
		apertura(0);
	}
}


/**/
void * productor()
{
	for (int i = 0; i < 20 ; i++)
	{
		cierre(0);
		for (int j = 0; j < 2; j++)
		{
			if ((semctl(semid, GETVAL,1))!=0)
			{
				close(j+2)
			}if (i == iteraciones)
			{
				//Produce '@'
			}else{
				//Produce x
			}
			apertura(j+4);
			break;
		}
		apertura();
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
		semctl(idSem,0,SETVAL,2);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,1);
		semctl(idSem,3,SETVAL,1);
	}

	if (flag == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			cierre(0);
			secCrit[0] = 'x';
			printf("\nProductor %d: %c\n",flag, secCrit[0]);
			apertura(1);
		}
	}
	if (flag == 2)
	{
			cierre(1);
			secCrit[0] = 'a';
			printf("\nProductor %d: %c\n",flag, secCrit[0]);
			apertura(2);
	}
	if (flag == 3)
	{
			cierre(2);
			secCrit[0] = 'a';
			printf("\nProductor %d: %c\n",flag, secCrit[0]);
			apertura(3);
	}
}

