#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void * consumidor(void*);
void * productor(void*);
void cierre(int numSem);
void apertura(int numSem);

//int secCrit;
char secCrit[1][2];
int idSem;

int main(){

pthread_t hilos[4];

int prod1 = pthread_create(&hilos[0], NULL, productor, 0);
int cons1 = pthread_create(&hilos[1], NULL, consumidor, 0);
int prod2 = pthread_create(&hilos[2], NULL, productor, (int*)1);
int cons2 = pthread_create(&hilos[3], NULL, consumidor, (int*)1);


if((prod1==-1)||(cons1==-1)||(cons2== -1)|| (prod2 == -1)){
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

void * productor(void* in){
	//paso 0:creación de la llave
	key_t key =ftok("/bin/ls",'b');//path  a un archivo
	//paso1:creación del mec de sincronización
	idSem = semget(key,4,0666 | IPC_CREAT | IPC_EXCL);//tarea
	if(idSem==-1){
		//ligado al semáforo
		idSem = semget(key,4,0666);	
		if(idSem==-1){
			printf("\nError en ligarse");
			exit(1);
		}
	}
	else{
		//inicialización del semáforo
		semctl(idSem,0,SETVAL,1);
		semctl(idSem,1,SETVAL,0);
		semctl(idSem,2,SETVAL,0);
		semctl(idSem,3,SETVAL,0);

}	
	if (in == 0)
	{
		for(int i=0;i<20;i++){//producciones en la sección crítica
			if(secCrit[0][0]=='\0'){
			cierre(0);
				secCrit[0][0] = 'a';	
				printf("\n ProductoA%d: %c \n",i, secCrit[0][0] );
			apertura(1);
			}
		}	
	}else{
			for(int i=0;i<20;i++){//producciones en la sección crítica
			if(secCrit[0][1]=='\0'){
			cierre(2); 
				secCrit[0][1]= 'b';				
				printf("\n ProductoB%d %c \n",i, secCrit[0][1] );
			apertura(3);
			}
		}	
	}

//solamente una vez se debe crear e inicializar el mecanismo de sincronización
}

void * consumidor(void * in){
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
	if (in == 0)
	{

		for(int i=0;i<20;i++){//consumos en la sección crítica
			if(secCrit[0][0]=='\0'){
			cierre(1);
			printf("\n ConsumoA%d: %c\n",i,secCrit[0][0]);
			secCrit[0][0] = '\0';
			apertura(2);
			}
		}
	}else
	{
		for(int i=0;i<20;i++){//consumos en la sección crítica
			if(secCrit[0][1]=='\0'){
			cierre(3);
			printf("\n ConsumoB%d: %c\n",i,secCrit[0][1]);
			secCrit[0][1] = '\0';
			apertura(0);
			}
		}
	}

}





