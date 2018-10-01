#makefile
#Archivo makefile simple
all: muestreo

muestreo.o: muestreo.c 
	gcc -c muestreo.c -Wall

archivos.o: archivos.c
	gcc -c archivos.c -Wall

procesamiento.o : archivos.c 
	gcc -c procesamiento.c -Wall

muestreo: procesamiento.o archivos.o muestreo.o
	gcc procesamiento.o archivos.o muestreo.o -o muestreo -lm 

