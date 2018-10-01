#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <string>
#include <iostream>
using namespace std;

void * productorFun(void *);
void * consumidorFun(void *);
int cierre(int sem_num);
int apertura(int sem_num);

int secCritTel[5];
int secCritMen[5];
int semid;
int iteraciones = 5000;
int cont = 0;
int main(){

	pthread_t *hilos;
	int productor;
	int consumidor;
	int *num = (int *) malloc(sizeof(int)*7);

	hilos = (pthread_t *) malloc (sizeof(pthread_t)*7);

	for(int i = 0; i < 4; i++){

		num[i] = i;
		productor = pthread_create(&hilos[i], NULL, productorFun, &num[i]);


		if(productor == -1){
			printf("ERROR, al crear el productor");
			exit(1);
		}

	}

	for(int i = 4; i < 7; i++){

		num[i] = i;
		consumidor = pthread_create(&hilos[i], NULL, consumidorFun, &num[i]);

		if(consumidor == -1){
			printf("ERROR, al crear el consumidor");
			exit(1);
		}

	}

 

	for(int i = 0; i < 7; i++){
		pthread_join(hilos[i],NULL);
	}



	return 0;
}

void * productorFun(void * num){
	int *lugar = (int *) num;
	key_t llave1 = ftok("/bin/ls",'b'); //creacion de llave
	semid = semget(llave1,24,0666 | IPC_CREAT | IPC_EXCL);						  //creacion del semaforo
	if(semid == -1){
		//ligado al semaforo
		semid = semget(llave1,24,0666);

		if(semid == -1){
			printf("Error al ligarse al semaforo\n");
			exit(1);
		}

	}else{
		//inicia el semaforo
		semctl(semid,0,SETVAL,5);
		semctl(semid,1,SETVAL,0);
		semctl(semid,2,SETVAL,5);
		semctl(semid,3,SETVAL,0);
		for(int i = 4; i < 9; i++)
			semctl(semid,i,SETVAL,1);	
		for(int i = 9; i < 14; i++)
			semctl(semid,i,SETVAL,0);
		for(int i = 14; i < 19; i++)
			semctl(semid,i,SETVAL,1);
		for(int i = 19; i < 24; i++)
			semctl(semid,i,SETVAL,0);
	}

	for(int i = 0; i < iteraciones+1; i++){	// Producciones en la seccion critica
		while(cierre(0)==-1){}
		for(int j = 0; j < 5; j++){
			if((semctl(semid,j+4,GETVAL,1))!=0){
				cierre(j+4);
				if(i==iteraciones){
					secCritTel[j]=-1;
					printf("Produce: -1 %d\n",*lugar+1);
				}else{
					secCritTel[j] = 0;
					for(int x = 1; x < 1000000; x *= 10)
						secCritTel[j]+=(*lugar+1)*x;
					printf("Produce: %d\n",secCritTel[j]);
				}
				apertura(j+9);
				break;
			}
		}
		apertura(1);
		
		cierre(2);
		for(int j = 0; j < 5; j++){
			if((semctl(semid,j+14,GETVAL,1))!=0){
				cierre(j+14);
				if(i==iteraciones){
					secCritMen[j]=-1;
					printf("Produce: Mensaje %d %d\n",secCritMen[j],*lugar+1);
				}else{
					secCritMen[j] = (*lugar+1);
					printf("Produce: Mensaje %d\n",secCritMen[j]);
				}
				apertura(j+19);
				break;
			}
		}
		apertura(3);
	}
	printf("Termino productor: %d\n",*lugar);
	pthread_exit(NULL);
}

void * consumidorFun(void * num){
	int *lugar = (int *) num;
	key_t llave1 = ftok("/bin/ls",'b'); //creacion de llave
	semid = semget(llave1,24,0666 | IPC_CREAT | IPC_EXCL);						  //creacion del semaforo
	if(semid == -1){
		//ligado al semaforo
		semid = semget(llave1,24,0666);

		if(semid == -1){
			printf("Error al ligarse al semaforo\n");
			exit(1);
		}

	}else{
		//inicia el semaforo
		semctl(semid,0,SETVAL,5);
		semctl(semid,1,SETVAL,0);
		semctl(semid,2,SETVAL,5);
		semctl(semid,3,SETVAL,0);
		for(int i = 4; i < 9; i++)
			semctl(semid,i,SETVAL,1);	
		for(int i = 9; i < 14; i++)
			semctl(semid,i,SETVAL,0);
		for(int i = 14; i < 19; i++)
			semctl(semid,i,SETVAL,1);
		for(int i = 19; i < 24; i++)
			semctl(semid,i,SETVAL,0);
	}


	while(cont<8){// Consumos en la seccion critica
		if((semctl(semid,1,GETVAL,1))!=0){
			cierre(1);
			for(int j = 0; j < 5; j++){
				if((semctl(semid,j+9,GETVAL,1))!=0){
				cierre(j+9);
				printf("Consume: %d\n",secCritTel[j]);
				if(secCritTel[j]==-1){
					cont++;
				}
				apertura(j+4);
				break;
			}
		}
		apertura(0);
		}
		if((semctl(semid,3,GETVAL,1))!=0){
			cierre(3);
			for(int j = 0; j < 5; j++){
				if((semctl(semid,j+19,GETVAL,1))!=0){
				cierre(j+19);
				printf("Consume: Mensaje %d\n",secCritMen[j]);
				if(secCritMen[j]==-1){
					cont++;
				}
				apertura(j+14);
				break;
			}
		}
		apertura(2);
		}
		if(cont == 8){
			break;
		}
	}
		for(int i = 0; i < 24; i++)
		semctl(semid,i,IPC_RMID,0);

	printf("Termino");
	pthread_exit(NULL);


}

int cierre(int sem_num){
	struct sembuf operaciones[1];
	operaciones[0].sem_num = sem_num;
	operaciones[0].sem_op = -1;
	operaciones[0].sem_flg = SEM_UNDO;
	return semop(semid,operaciones,1);
}

int apertura(int sem_num){
	struct sembuf operaciones[1];
	operaciones[0].sem_num = sem_num;
	operaciones[0].sem_op = 1;
	operaciones[0].sem_flg = SEM_UNDO;
	return semop(semid,operaciones,1);
}

