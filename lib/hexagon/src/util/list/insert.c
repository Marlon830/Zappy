/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include "hexagon/util/math.h"

void list_insert(list_t *self, size_t i, void *value)
{
    list_node_t *curr_node = list_atn(self, i);
    list_node_t *new_node = list_node_new(value);

    if (curr_node) {
        new_node->prev = curr_node->prev;
        new_node->next = curr_node;
        if (curr_node->prev)
            curr_node->prev->next = new_node;
        if (curr_node == self->first)
            self->first = new_node;
        curr_node->prev = new_node;
    } else {
        if (self->last)
            self->last->next = new_node;
        new_node->prev = self->last;
        if (!self->first)
            self->first = new_node;
        self->last = new_node;
    }
    self->size++;
}
