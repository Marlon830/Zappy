/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

void *list_sub(list_t *self)
{
    return list_remove(self, list_len(self) - 1);
}
