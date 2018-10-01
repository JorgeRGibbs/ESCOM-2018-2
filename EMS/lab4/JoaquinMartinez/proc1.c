#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 4

void procesoHijo(int np){
  //sleep(5);
  printf("Proceso hijo %d terminado con pid %d\n",np,getpid());
  while(1);
  exit(np);
}

void procesoPadre(){
  //sleep(5);
  int np,estado;
  pid_t pid_hijo;
  printf("Proceso padre ejecutado con pid %d\n",getpid());
  for (np = 0; np < NUM_PROC; ++np)
  {
    pid_hijo = wait(&estado);
    printf("Proceso hijo %d terminado con pid %d\n",estado>>8, pid_hijo);
  }
  exit(0);
}

int main(){
 pid_t pid;
 printf("Probando Procesos\n");

 for(int np = 0; np < NUM_PROC; np++){
  pid = fork();
  if(pid== -1){
  printf("NO SE PUDO EJECUTAR EL CODIGO\n");
  exit(EXIT_FAILURE);
  }
  if (!pid)
  {
    procesoHijo(np);
  }
 }
 procesoPadre();
 return 0;
}
