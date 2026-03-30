/*
** EPITECH PROJECT, 2024
** argument
** File description:
** file for arguments functions
*/

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "argument.h"

void arguments_parse(list_t *args, int argc, const char **argv)
{
    argument_t *argument;

    for (int i = 1; i < argc; i++) {
        argument = arguments_find(args, argv[i]);
        if (argument && i + argument->args < argc) {
            argument->callback(&argv[i + 1]);
            i += argument->args == -1 ?
                arguments_count_variadic(&argv[i + 1]) :
                argument->args;
            continue;
        }
        fprintf(stderr, "Invalid argument or argument count: %s\n", argv[i]);
        exit(84);
    }
}
