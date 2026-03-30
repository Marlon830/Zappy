/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

void *list_remove(list_t *self, size_t i)
{
    list_node_t *node = list_atn(self, i);
    void *value;

    if (!node)
        return NULL;
    value = node->value;
    list_remove_node(self, node);
    return value;
}

void list_remove_node(list_t *self, list_node_t *node)
{
    if (!node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (self->first == node)
        self->first = node->next;
    if (self->last == node)
        self->last = node->prev;
    list_node_delete(node);
    self->size--;
}
