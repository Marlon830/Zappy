/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

void *list_pop(list_t *self)
{
    return list_remove(self, 0);
}
