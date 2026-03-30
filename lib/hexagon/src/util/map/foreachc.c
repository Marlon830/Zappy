/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

void map_foreachc(map_t *self, void *context, map_foreachc_lamb_t *callback)
{
    for (size_t i = 0; i < self->size; i++) {
        if (self->values[i].key)
            callback(context, self->values[i].key, self->values[i].value);
    }
}
