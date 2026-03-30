/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/map.h"

#include <stdint.h>

size_t map_hash(map_t *self, void *key)
{
    const uint64_t fnv_prime = 0x00000100000001b3;
    const uint64_t fnv_offset_basis = 0xcbf29ce484222325;
    uint64_t hash = fnv_offset_basis;
    uint8_t *bytes = (uint8_t *) key;

    for (size_t i = 0; i < self->key_size; i++) {
        hash ^= bytes[i];
        hash *= fnv_prime;
    }
    return hash;
}
