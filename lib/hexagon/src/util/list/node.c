/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include "hexagon/util/mem.h"

list_node_t *list_node_new(void *value)
{
    list_node_t *self = STRUCT_NEW(list_node);

    *self = (list_node_t) {
        .value = value,
        .next = NULL,
        .prev = NULL
    };
    return self;
}

void list_node_delete(list_node_t *self)
{
    mem_free(self);
}
