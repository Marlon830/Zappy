/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

#include "hexagon/util/mem.h"

#include <string.h>

static void map_resize_remap(map_t *self, map_entry_t *new_values, size_t size)
{
    size_t hash;
    size_t bucket_index;

    for (size_t index = 0; index < self->size; index++) {
        if (!self->values[index].key)
            continue;
        hash = map_hash(self, self->values[index].key);
        for (bucket_index = hash % size; new_values[bucket_index].key;
            bucket_index = (bucket_index + 1) % size);
        new_values[bucket_index] = self->values[index];
    }
}

void map_resize(map_t *self, size_t size)
{
    map_entry_t *new_values = mem_alloc(size * sizeof(map_entry_t));

    memset(new_values, 0, size * sizeof(map_entry_t));
    if (self->values) {
        map_resize_remap(self, new_values, size);
        mem_free(self->values);
    }
    self->values = new_values;
    self->size = size;
}
