/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

#include "hexagon/util/mem.h"
#include "hexagon/util/c.h"

#include <stddef.h>

map_t *map_new(size_t key_size)
{
    STRUCT_NEWIN(map, self);
    *self = (map_t) {0};
    self->key_size = key_size;
    return self;
}

void map_delete(map_t *self)
{
    map_clear(self);
    mem_free(self);
}
