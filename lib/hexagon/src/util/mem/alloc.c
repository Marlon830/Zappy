/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/mem.h"

#include <assert.h>
#include <stdlib.h>

void *mem_alloc(size_t size)
{
    void *ptr = malloc(size);

    assert(ptr);
    return ptr;
}
