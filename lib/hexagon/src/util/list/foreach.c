/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include <stddef.h>

void list_foreach(list_t *self, list_foreach_lamb_t *callback)
{
    list_node_t *curr = list_atn(self, 0);
    list_node_t *next = curr ? curr->next : NULL;

    for (; curr;) {
        callback(curr->value);
        curr = next;
        next = next ? next->next : NULL;
    }
}
