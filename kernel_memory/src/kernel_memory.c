#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include "conexiones.h"

int main(void) {
    t_log* logger = log_create("memory.log", "MEMORY", 1, LOG_LEVEL_INFO);
    t_config* config = config_create("cfg/memory.config");

    if (config == NULL) {
        log_error(logger, "No se pudo leer el config");
        return EXIT_FAILURE;
    }

    char* puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
    
    // 1. Iniciamos el servidor
    int socket_servidor = iniciar_servidor(puerto);
    log_info(logger, "Memoria lista para recibir a la CPU...");

    // 2. Esperamos a que la CPU se conecte
    int socket_cliente = esperar_cliente(socket_servidor);
    
    if (socket_cliente != -1) {
        log_info(logger, "¡CPU Conectada con éxito!");
    }

    // Limpieza
    log_destroy(logger);
    config_destroy(config);
    return 0;
}