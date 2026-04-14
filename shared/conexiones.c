#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int crear_conexion(char *ip, char* puerto){
    struct addrinfo hints;
    struct addrinfo *server_info;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(ip, puerto, &hints, &server_info);

    int socket_cliente = socket(
        server_info->ai_family,
        server_info->ai_socktype,
        server_info->ai_protocol
    );

    if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1){
        perror("Error en connect");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info);

    return socket_cliente;
}



int iniciar_servidor(char* puerto){
    struct addrinfo hints, *server_info;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, puerto, &hints, &server_info);

    int socket_servidor = socket(
        server_info->ai_family,
        server_info->ai_socktype,
        server_info->ai_protocol
    );

    setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));

    bind(socket_servidor, server_info->ai_addr, server_info->ai_addrlen);

    listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(server_info);

    return socket_servidor;
}


int esperar_cliente(int socket_servidor){
    int cliente = accept(socket_servidor, NULL, NULL);
    return cliente;
}


void* atender_cliente(void* arg){
    int cliente = *(int*)arg;
    free(arg);

    // recibir mensajes
    while(1) {
        // recv(...)
    }

    return NULL;
}
void liberar_conexion(int socket) {
    if (socket != -1) {
        close(socket);
    }
}