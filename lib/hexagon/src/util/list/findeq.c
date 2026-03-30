/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include <string.h>
#include <limits.h>

size_t list_findeq(list_t *self, void *value, size_t member_size)
{
    size_t i = 0;
    list_node_t *node = self->first;

    for (; i < self->size; i++) {
        if (memcmp(node->value, value, member_size) == 0)
            return i;
        node = node->next;
    }
    return ULONG_MAX;
}
