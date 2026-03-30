/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

void map_foreach(map_t *self, map_foreach_lamb_t *callback)
{
    for (size_t i = 0; i < self->size; i++) {
        if (self->values[i].key)
            callback(self->values[i].key, self->values[i].value);
    }
}
