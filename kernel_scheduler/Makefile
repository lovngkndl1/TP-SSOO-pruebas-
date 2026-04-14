CC = gcc
CFLAGS = -I/home/utnso/TP-SSOO-pruebas-/shared -Wall
LIBS = -lcommons -lpthread

# El archivo se llama kernel_scheduler.c segun tu carpeta src
SRCS = src/kernel_scheduler.c /home/utnso/TP-SSOO-pruebas-/shared/conexiones.c
OBJ = bin/kernel

all: bin
	$(CC) $(SRCS) -o $(OBJ) $(CFLAGS) $(LIBS)

bin:
	mkdir -p bin

clean:
	rm -rf bin