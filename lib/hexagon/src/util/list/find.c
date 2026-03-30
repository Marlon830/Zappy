/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include <limits.h>

size_t list_find(list_t *self, void *value)
{
    size_t i = 0;
    list_node_t *node = self->first;

    for (; i < self->size; i++) {
        if (node->value == value)
            return i;
        node = node->next;
    }
    return ULONG_MAX;
}
