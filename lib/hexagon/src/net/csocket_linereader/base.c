/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_linereader.h"

#include "hexagon/util/mem.h"

csocket_linereader_t *csocket_linereader_new(csocket_t *socket)
{
    STRUCT_NEWIN(csocket_linereader, self);
    *self = (csocket_linereader_t) {
        .socket = socket,
        0
    };
    return self;
}

void csocket_linereader_delete(csocket_linereader_t *self)
{
    if (self->buff)
        mem_free(self->buff);
    mem_free(self);
}
