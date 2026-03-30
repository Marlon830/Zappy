/*
** EPITECH PROJECT, 2024
** port
** File description:
** file for port functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "argument.h"
#include "server.h"

void command_port(const char **args)
{
    server_t *server = server_get();
    char *ptr;

    server->port = (int)strtol(args[0], &ptr, 10);
    if (*ptr != '\0' || server->port < 0 || server->port > 65535) {
        fprintf(stderr, "Invalid port\n");
        exit(84);
    }
}
