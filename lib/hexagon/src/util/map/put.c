/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

#include "hexagon/util/mem.h"

#include <string.h>

void map_put(map_t *self, void *key, void *value)
{
    size_t hash;
    size_t index;

    if (self->size == 0)
        map_resize(self, MAP_INITSIZE);
    else if (self->count * 1.0 / self->size * 1.0 > MAP_RESIZETHRESHOLD)
        map_resize(self, self->size * 2);
    hash = map_hash(self, key);
    for (index = hash % self->size; self->values[index].key;
        index = (index + 1) % self->size);
    self->values[index] = (map_entry_t) { mem_alloc(self->key_size), value };
    memcpy(self->values[index].key, key, self->key_size);
    self->count++;
}
