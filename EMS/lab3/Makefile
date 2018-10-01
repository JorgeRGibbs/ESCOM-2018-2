#makefile
#Archivo makefile simple
#das verdammt c datei ist kaput, ich muss das reparieren.
PROYECTO=principal
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm 
CC=gcc 

all: $(PROYECTO)

%.o: %.c 
	$(CC) -c $< $(CFLAGS)

#muestreo.o: muestreo.c 
#	gcc -c muestreo.c $(CFLAGS)

#archivos.o: archivos.c
#	gcc -c archivos.c $(CFLAGS)

#procesamiento.o : archivos.c 
#	gcc -c procesamiento.c $(CFLAGS)

$(PROYECTO): procesamiento.o datos.o procesos.o principal.o 

#SRC=$(wildcard *.c)
#test: $(SRC)
#	$(CC)  $^ -O $@ $(CFLAGS) $(LDFLAGS)
#$(PROYECTO): $(wildcard *.o)
#$(PROYECTO): *.c 
#	$(patsubst %.c,%.o,x.c.c *.c)
#	$(PROYECTO):(patsubst %.c,%.o,$(wildcard *.c))
#obj := $(patsubst %.c,%.o,$(wildcard *.c))
#foo : $(obj)
#	cc -o foo $(PROYECTO)

#$(subst ee,EE,feet on the street)
	#gcc procesamiento.o archivos.o muestreo.o -o $(PROYECTO) $(LFLAGS)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
		sudo cp $(PROYECTO)  $(DESTDIR)
uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)
clean:
	rm -f *.o $(PROYECTO)
