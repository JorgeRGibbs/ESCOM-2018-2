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

void imprimirArreglo(int *datos){
  register int i;
  for (int i = 0; i < n; ++i)
  {
    /* code */
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

int main(){
  int *datos;
  datos = reservaMemoria();
  llenarArreglo(datos);
  imprimirArreglo();
  free(datos);  
 return 0;
}

