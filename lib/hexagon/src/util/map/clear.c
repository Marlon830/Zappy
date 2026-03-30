/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

#include "hexagon/util/mem.h"

#include <stddef.h>

void map_clear(map_t *self)
{
    for (size_t i = 0; i < self->size; i++) {
        if (self->values[i].key)
            mem_free(self->values[i].key);
    }
    if (self->values)
        mem_free(self->values);
    self->values = NULL;
    self->size = 0;
}
