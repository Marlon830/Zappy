/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

size_t csocket_getin(csocket_t *self)
{
    return self->in_buff_ceil - self->in_buff_ptr;
}

size_t csocket_getout(csocket_t *self)
{
    return self->out_buff_ptr - self->out_buff;
}
