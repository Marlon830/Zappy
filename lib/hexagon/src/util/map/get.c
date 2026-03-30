/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

void *map_get(map_t *self, void *key)
{
    size_t hash = map_hash(self, key);

    for (size_t index = hash % self->size; self->values[index].key;
        index = (index + 1) % self->size) {
        if (map_hash(self, self->values[index].key) == hash)
            return self->values[index].value;
    }
    return NULL;
}
