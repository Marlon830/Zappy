/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_linereader.h"

size_t csocket_linereader_getbuffsize(csocket_linereader_t *self)
{
    return self->buff_size;
}
