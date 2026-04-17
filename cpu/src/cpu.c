#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
#include <unistd.h>
#include "/home/utnso/TP-SSOO-pruebas-/shared/conexiones.h"

t_log* logger;

// ================== THREAD KERNEL_MEMO ==================

void* conectar_memoria(void* arg) {
    char** data = (char**) arg;

    char* ip = data[0];
    char* puerto = data[1];

    while(1) {
        log_info(logger, "Intentando conectar a Memoria...");

        int conexion = crear_conexion(ip, puerto);

        if(conexion != -1) {
            log_info(logger, "¡Conectado a Memoria con éxito!");
            break;
        }

        log_warning(logger, "No se pudo conectar a Memoria, reintentando...");
        sleep(2);
    }

    return NULL;
}

// ================== MAIN ==================

int main(int argc, char* argv[]) {

    t_log* logger_local = log_create("cpu.log", "CPU_LOG", 1, LOG_LEVEL_INFO);
    logger = logger_local;

    t_config* config = config_create("cfg/cpu.config");

    if (config == NULL) {
        log_error(logger, "No se pudo leer el config");
        return EXIT_FAILURE;
    }

    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    char* puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");

    log_info(logger, "CPU Iniciada");

    // ================== HILO MEMORIA ==================

    pthread_t hilo_memoria;

    char* datos[2] = {ip_memoria, puerto_memoria};

    pthread_create(&hilo_memoria, NULL, conectar_memoria, datos);
    pthread_detach(hilo_memoria);

    // ================== SERVIDOR ==================

    log_info(logger, "Esperando al Kernel Scheduler en puerto %s...", puerto_escucha);

    int socket_servidor = iniciar_servidor(puerto_escucha);
    int socket_kernel = esperar_cliente(socket_servidor);

    log_info(logger, "¡Kernel Scheduler conectado!");

    // ================== CLEANUP ==================

    log_destroy(logger);
    config_destroy(config);

    return 0;
}