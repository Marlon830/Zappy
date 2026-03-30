/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/mem.h"

#include <stdint.h>
#include <string.h>

void *mem_find(void *_haystack, size_t haystack_size,
    const void *_needle, size_t needle_size)
{
    uint8_t *haystack = _haystack;
    const uint8_t *needle = _needle;

    if (!haystack_size || !needle_size)
        return NULL;
    while (haystack_size - needle_size + 1 > 0) {
        if (memcmp(haystack, needle, needle_size) == 0)
            return haystack;
        haystack++;
        haystack_size--;
    }
    return NULL;
}
