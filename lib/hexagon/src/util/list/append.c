/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

void list_append(list_t *self, void *value)
{
    list_insert(self, list_len(self), value);
}
