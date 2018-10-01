#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	float num1 = 23, num2 = 12,suma,resta;
	pid_t pid,pid_hijo;
	int estado;
	printf("Probando procesos...");
	pid = fork();
	if(!pid){
		printf("Procesos hijo ejecutado con pid %d",getpid());
		suma = num1 + num2;
		printf("Suma: %f\n",suma);
		exit(0);
	}else{
		printf("Proceso padre ejecutado con pid %d",getpid());
		resta = num1-num2;
		printf("Resta: %f\n",resta);
		pid_hijo = wait(&estado);
		printf("Procesos hijo terminado con pid %d\n",pid_hijo);	
		exit(0);
	}
	return 0;
}
