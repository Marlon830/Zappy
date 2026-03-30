/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/mem.h"

#include <assert.h>
#include <stdlib.h>

void mem_realloc(void **ptr, size_t size)
{
    assert(ptr);
    *ptr = realloc(*ptr, size);
    assert(*ptr);
}
