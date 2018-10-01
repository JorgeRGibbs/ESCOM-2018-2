#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 2
#define n 32

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

void imprimirArreglo(int *datos){
  register int i;
  for (i = 0; i < n; ++i)
  {
    printf("%d ",datos[i]);
  }
  printf("\n");
}

void llenarArreglo(int *datos){
  register int i;
  srand(getpid());
  for (i = 0; i < n; ++i)
  {
    datos[i] = rand()%255;
  }
}

int mayorArreglo(int *datos){
  register int i, mayor;
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

int menorArreglo(int *datos){
  register int i, menor;
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



void procesoHijo(int np, int *datos){
  int mayor,menor;
  printf("Proceso hijo %d terminado con pid %d\n",np,getpid());
  //while(1);
  if ( np == 0 )
  {
    mayor = mayorArreglo(datos);
    exit(mayor);
  }else if(np == 1){
    menor = menorArreglo(datos);
    exit(menor);
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
    printf("Proceso hijo %d terminado y retorno %d\n", pid_hijo,estado>>8);
  }
  exit(0);
}

int main(){
  int *datos;
  datos = reservaMemoria();
  llenarArreglo(datos);
  imprimirArreglo(datos);
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
    procesoHijo(np,datos);
  }
 }
 procesoPadre();
 free(datos);
 return 0;
}
