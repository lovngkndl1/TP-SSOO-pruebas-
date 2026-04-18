#ifndef CONEXIONES_H
#define CONEXIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// sockets
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// threads (para servers multihilo)
#include <pthread.h>

//////////////////////////////////////////////////
// PROTOCOLO DE COMUNICACIÓN
//////////////////////////////////////////////////

typedef enum {
    IDENTIFICACION_IO, // Para que la IO se presente al Kernel
    IO_GEN_SLEEP,      // La operación de dormir
    IO_OK,             // Para avisar que terminó
    DESCONEXION        // Por si se corta la comunicación
} op_code;

// Estructura para recibir el código de operación
int recibir_operacion(int socket_cliente);

//////////////////////////////////////////////////
// CLIENTE
//////////////////////////////////////////////////

/**
 * @brief Crea una conexión hacia un servidor
 * 
 * @param ip IP del servidor
 * @param puerto Puerto del servidor
 * @return int socket conectado
 */
int crear_conexion(char* ip, char* puerto);

//////////////////////////////////////////////////
// SERVIDOR
//////////////////////////////////////////////////

/**
 * @brief Inicia un servidor escuchando en un puerto
 * 
 * @param puerto Puerto a escuchar
 * @return int socket servidor
 */
int iniciar_servidor(char* puerto);

/**
 * @brief Espera la conexión de un cliente
 * 
 * @param socket_servidor socket del servidor
 * @return int socket del cliente
 */
int esperar_cliente(int socket_servidor);

//////////////////////////////////////////////////
// UTILIDADES
//////////////////////////////////////////////////

/**
 * @brief Libera una conexión
 * 
 * @param socket socket a cerrar
 */
void liberar_conexion(int socket);

/**
 * @brief Manejo de errores simple
 */
void manejar_error(char* mensaje);

//////////////////////////////////////////////////
// SERVER MULTIHILO (helper opcional)
//////////////////////////////////////////////////

/**
 * @brief Función genérica para crear un hilo por cliente
 * 
 * @param socket_cliente socket del cliente
 * @param funcion función que atiende al cliente
 */
void crear_hilo_cliente(int socket_cliente, void* (*funcion)(void*));

#endif