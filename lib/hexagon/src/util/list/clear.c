/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

void list_clear(list_t *self)
{
    while (list_len(self) > 0)
        list_pop(self);
}
