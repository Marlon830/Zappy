/*
** EPITECH PROJECT, 2024
** width
** File description:
** file for width functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "argument.h"
#include "server.h"

void command_width(const char **args)
{
    server_t *server = server_get();
    char *ptr;

    server->game->width = (int)strtol(args[0], &ptr, 10);
    if (*ptr != '\0' || server->game->width < 1) {
        fprintf(stderr, "Invalid width\n");
        exit(84);
    }
}
