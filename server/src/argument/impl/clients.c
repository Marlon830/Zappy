/*
** EPITECH PROJECT, 2024
** clients
** File description:
** file for clients functions
*/

#include "server.h"

#include <stdio.h>
#include <stdlib.h>

void command_clients_nb(const char **args)
{
    server_t *server = server_get();
    char *ptr;

    server->ppt = (int)strtol(args[0], &ptr, 10);
    if (*ptr != '\0' || server->ppt < 1) {
        fprintf(stderr, "Invalid clients_nb\n");
        exit(84);
    }
}
