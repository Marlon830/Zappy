/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

list_node_t *list_atn(list_t *self, size_t i)
{
    list_node_t *node = self->first;

    for (; node && i; i--)
        node = node->next;
    return node;
}
