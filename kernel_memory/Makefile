CC = gcc
CFLAGS = -I/home/utnso/TP-SSOO-pruebas-/shared -Wall
LIBS = -lcommons -lpthread

SRCS = src/kernel_memory.c /home/utnso/TP-SSOO-pruebas-/shared/conexiones.c
OBJ = bin/memory

all: bin
	$(CC) $(SRCS) -o $(OBJ) $(CFLAGS) $(LIBS)

bin:
	mkdir -p bin

clean:
	rm -rf bin