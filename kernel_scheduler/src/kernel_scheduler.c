#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
#include "conexiones.h"

t_log* logger;

// ================== THREAD MULTI CLIENTES ==================

void* atender_cliente(void* arg) {
    int socket_cliente = *(int*)arg;
    free(arg);

    log_info(logger, "Nuevo cliente conectado");

    // solo se inicializa el socket
    while(1) {
        // acá ira recv()
        sleep(5); 
        //pongo sleep mientras tanto hasta que implemente recv y sea bloqueante
    }

    return NULL;
}

// ================== MAIN ==================

int main(int argc, char* argv[]) {

    logger = log_create("kernel_scheduler.log", "KERNEL", 1, LOG_LEVEL_INFO);

    t_config* config = config_create("cfg/kernel_scheduler.config");

    if(config == NULL){
        log_error(logger, "No se pudo leer el config");
        return EXIT_FAILURE;
    }

    // ================== CONFIG ==================

    char* puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");

    char* ip_cpu = config_get_string_value(config, "IP_CPU");
    char* puerto_cpu = config_get_string_value(config, "PUERTO_CPU");

    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");

    // ================== LOG INICIAL ==================

    log_info(logger, "Kernel Scheduler iniciado");

    // ================== CONEXION A MEMORIA ==================

    log_info(logger, "Conectando a Memoria...");
    int conexion_memoria = crear_conexion(ip_memoria, puerto_memoria);

    if(conexion_memoria != -1){
        log_info(logger, "Conectado a Memoria");
    }

    // ================== CONEXION A CPU ==================

    log_info(logger, "Conectando a CPU...");
    int conexion_cpu = crear_conexion(ip_cpu, puerto_cpu);

    if(conexion_cpu != -1){
        log_info(logger, "Conectado a CPU");
    }

    // ================== SERVIDOR PARA IO ==================

    log_info(logger, "Levantando servidor para IO en puerto %s...", puerto_escucha);

    int server_fd = iniciar_servidor(puerto_escucha);

    // ================== ACEPTAR CLIENTES ==================

    while(1){
        int cliente_fd = esperar_cliente(server_fd);

        log_info(logger, "Se conectó un IO");

        pthread_t hilo;
        int* p = malloc(sizeof(int));
        *p = cliente_fd;

        pthread_create(&hilo, NULL, atender_cliente, p);
        pthread_detach(hilo);
    }

    // ================== LIBERAR MEMORIA ==================

    liberar_conexion(conexion_cpu);
    liberar_conexion(conexion_memoria);

    log_destroy(logger);
    config_destroy(config);

    return 0;
}