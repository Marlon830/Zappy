/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_block.h"

size_t csocket_block_getsize(csocket_block_t *self)
{
    return self->size;
}
