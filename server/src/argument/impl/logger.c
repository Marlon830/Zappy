/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server.h"

#include "hexagon/util/logger.h"

#include <stdio.h>
#include <stdlib.h>

void command_logger_level(const char **args)
{
    server_t *server = server_get();
    const logger_level_t *level = logger_findlevel(args[0]);

    if (!level) {
        fprintf(stderr, "Invalid logger level '%s'", args[0]);
        exit(84);
    }
    logger_setthreshold(server->logger, level);
}
