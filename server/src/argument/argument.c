/*
** EPITECH PROJECT, 2024
** arguments
** File description:
** file for argument functions
*/

#include <malloc.h>
#include <string.h>
#include "argument.h"
#include "hexagon/util/mem.h"

argument_t *argument_new(argument_t argument)
{
    argument_t *new_argument = mem_alloc(sizeof(argument_t));

    new_argument->sflag = strdup(argument.sflag);
    new_argument->lflag = strdup(argument.lflag);
    new_argument->description = strdup(argument.description);
    new_argument->args = argument.args;
    new_argument->callback = argument.callback;
    return new_argument;
}

void argument_delete(argument_t *self)
{
    mem_free(self->sflag);
    mem_free(self->lflag);
    mem_free(self->description);
    mem_free(self);
}
