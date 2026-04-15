CC = gcc

CFLAGS = -I../shared -Wall -g
LIBS = -lcommons -lpthread

SRCS = src/kernel_scheduler.c ../shared/conexiones.c
OBJ = bin/kernel_scheduler

all: bin
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJ) $(LIBS)

bin:
	mkdir -p bin

clean:
	rm -rf bin