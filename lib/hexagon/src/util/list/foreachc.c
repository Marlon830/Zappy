/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include <stddef.h>

void list_foreachc(list_t *self,
    void *context, list_foreachc_lamb_t *callback)
{
    list_node_t *curr = list_atn(self, 0);
    list_node_t *next = curr ? curr->next : NULL;

    for (; curr;) {
        callback(context, curr->value);
        curr = next;
        next = next ? next->next : NULL;
    }
}
