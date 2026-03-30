/*
** EPITECH PROJECT, 2024
** freq
** File description:
** file for freq functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "argument.h"
#include "server.h"

void command_freq(const char **args)
{
    server_t *server = server_get();
    char *ptr;

    server->freq = (int)strtol(args[0], &ptr, 10);
    if (*ptr != '\0' || server->freq <= 0) {
        fprintf(stderr, "Invalid frequency\n");
        exit(84);
    }
}
