/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_linereader.h"

void csocket_linereader_clear(csocket_linereader_t *self)
{
    self->buff_ptr = self->buff + self->buff_size;
}
