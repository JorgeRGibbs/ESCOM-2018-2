#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main()
{
	int status;
	int pid_hijo;
	
	float num1 = 23, num2 = 12, suma, resta;
	printf("Probando procesos...\n");
	pid_t p = fork();
	if (!p)
	{
		printf("Proceso hijo con pid %d\n", getpid());
		suma = num1 + num2;
		printf("La suma es: %f \n", suma );
		exit(0);
	}else{
		sleep(5);
		printf("Proceso padre ejecutado con pid %d\n",getpid() );
		resta = num1 - num2;
		printf("La resta es: %f \n", resta );
		pid_hijo = wait(&status);
		printf("proceso hijo terminado con pid %d\n", pid_hijo);
	}
	return 0;
}
