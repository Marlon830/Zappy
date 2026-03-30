/*
** EPITECH PROJECT, 2024
** help
** File description:
** file for help functions
*/

#include "argument.h"
#include "argument.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>

#include "hexagon/util/c.h"

void print_argument(void *argument)
{
    argument_t *arg = argument;

    printf("  %-2s, %-20s %s\n", arg->sflag, arg->lflag, arg->description);
}

void command_help(UNUSED const char **args)
{
    server_t *server = server_get();

    printf("USAGE: ./zappy_server [OPTIONS]\n");
    printf("OPTIONS:\n");
    list_foreach(server->args, FUNC &print_argument);
    exit(0);
}
