#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 2

int *reservaMemoria(){
  int *mem;
  mem = (int*)malloc(sizeof(int)*n);
  if (!mem)
  {
    perror("Error al asignar memoria...\n");
    exit(EXIT_FAILURE);
  }
  return mem;
}

int llenarArreglo(int *datos){
  register int i;
  for (i = 0; i < n; ++i)
  {
    datos[i] = rand()%255;
  }
}

void mayorArreglo(int *datos){
  register int i, int mayor;
  mayor = datos[0];
  for (int i = 1; i < n; ++i)
  {
    if (datos[i]>mayor)
    {
      mayor = datos[i];
    }
  }
  return mayor;
}

void menorArreglo(int *datos){
  register int i, int menor;
  menor = datos[0];
  for (int i = 1; i < n; ++i)
  {
    if (datos[i]< menor)
    {
      menor = datos[i];
    }
  }
  return menor;
}



void procesoHijo(int np){
  printf("Proceso hijo %d terminado con pid %d\n",np,getpid());
  //while(1);
  if ( np == 0 )
  {
    mayorArreglo();
  }else if(np == 1){
    menorArreglo();
  }
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
