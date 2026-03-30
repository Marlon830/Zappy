/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_block.h"

uint8_t *csocket_block_getbuff(csocket_block_t *self)
{
    return self->buff;
}
