/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/mem.h"

#include <stddef.h>
#include <stdint.h>

uint8_t mem_firstlastbit(size_t n)
{
    size_t i = sizeof(i) * 8 - 1;

    while (i) {
        i--;
        if (n & (1 << i))
            return i;
    }
    return i;
}
