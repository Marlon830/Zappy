/*
** EPITECH PROJECT, 2024
** height
** File description:
** file for height functions
*/

#include "argument.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>

void command_height(const char **args)
{
    server_t *server = server_get();
    char *ptr;

    server->game->height = (int)strtol(args[0], &ptr, 10);
    if (*ptr != '\0' || server->game->height < 1) {
        fprintf(stderr, "Invalid height\n");
        exit(84);
    }
}
