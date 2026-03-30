/*
** EPITECH PROJECT, 2024
** util
** File description:
** file for util functions
*/

#include <strings.h>
#include "argument.h"

argument_t *arguments_find(list_t *args, const char *flag)
{
    argument_t *argument;

    for (list_node_t *node = args->first; node; node = node->next) {
        argument = node->value;
        if (strcasecmp(argument->sflag, flag) == 0 ||
            strcasecmp(argument->lflag, flag) == 0)
            return argument;
    }
    return NULL;
}

int arguments_count_variadic(const char **args)
{
    int count = 0;

    for (; args[count] && args[count][0] != '-'; count++);
    return count;
}
