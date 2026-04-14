#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include "/home/utnso/TP-SSOO-pruebas-/shared/conexiones.h"

int main(int argc, char* argv[]) {
    t_log* logger = log_create("cpu.log", "CPU_LOG", 1, LOG_LEVEL_INFO);
    t_config* config = config_create("cfg/cpu.config");

    if (config == NULL) {
        log_error(logger, "No se pudo leer el config");
        return EXIT_FAILURE;
    }

    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    char* puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");

    log_info(logger, "CPU Iniciada");

    log_info(logger, "Conectando a Memoria...");
    int conexion_memoria = crear_conexion(ip_memoria, puerto_memoria);
    
    if(conexion_memoria != -1) {
        log_info(logger, "¡Conectado a Memoria con éxito!");
    }

    log_info(logger, "Esperando al Kernel en puerto %s...", puerto_escucha);
    int socket_servidor = iniciar_servidor(puerto_escucha);
    int socket_kernel = esperar_cliente(socket_servidor);
    
    log_info(logger, "¡Kernel conectado!");

    log_destroy(logger);
    config_destroy(config);
    liberar_conexion(conexion_memoria); 
    
    return 0;
}