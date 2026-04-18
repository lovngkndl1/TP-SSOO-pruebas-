#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <commons/config.h>
#include <commons/log.h>
#include "../../shared/conexiones.h" 

int main(int argc, char* argv[]) {
    t_log* logger = log_create("io.log", "I/O", 1, LOG_LEVEL_INFO);
    t_config* config = config_create("cfg/generica.config");

    if (config == NULL) {
        log_error(logger, "No pude encontrar el config. ¿Está en cfg/generica.config?");
        return EXIT_FAILURE;
    }

    char* ip_kernel = config_get_string_value(config, "IP_KERNEL");
    char* puerto_kernel = config_get_string_value(config, "PUERTO_KERNEL");

    int fd_kernel = crear_conexion(ip_kernel, puerto_kernel);
    log_info(logger, "Conectado al Kernel. Esperando órdenes...");

    while (1) {
        int cod_op = recibir_operacion(fd_kernel); 
        
        switch (cod_op) {
            case IO_GEN_SLEEP:
                // Ahora sí recibimos las unidades reales del Kernel
                int unidades = recibir_unidades(fd_kernel);
                log_info(logger, "Me pidieron dormir %d unidades", unidades);
                
                int tiempo_unidad = config_get_int_value(config, "TIEMPO_UNIDAD_TRABAJO");
                
                // Dormimos (unidades * tiempo * 1000 para pasar a milisegundos)
                usleep(unidades * tiempo_unidad * 1000); 
                
                // Avisamos que terminamos
                int respuesta = IO_OK;
                send(fd_kernel, &respuesta, sizeof(int), 0);
                log_info(logger, "Dormido finalizado. Aviso enviado al Kernel.");
                break;
                
            case -1:
                log_error(logger, "Kernel se desconectó.");
                return EXIT_FAILURE;
                
            default:
                log_warning(logger, "Operación desconocida recibida.");
                break;
        }
    }

    return EXIT_SUCCESS;
}