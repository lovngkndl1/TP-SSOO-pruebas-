CC = gcc
CFLAGS = -I/home/utnso/TP-SSOO-pruebas-/shared -Wall
LIBS = -lcommons -lpthread

SRCS = src/cpu.c /home/utnso/TP-SSOO-pruebas-/shared/conexiones.c
OBJ = bin/cpu

all: bin
	$(CC) $(SRCS) -o $(OBJ) $(CFLAGS) $(LIBS)

bin:
	mkdir -p bin

clean:
	rm -rf bin