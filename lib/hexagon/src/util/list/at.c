/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

void *list_at(list_t *self, size_t i)
{
    list_node_t *node = list_atn(self, i);

    return node ? node->value : NULL;
}
