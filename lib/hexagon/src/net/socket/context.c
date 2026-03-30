/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/socket.h"

void socket_bindcontext(socket_t *self,
    void *context, socket_contextdeleter_t *context_deleter)
{
    self->context = context;
    self->context_deleter = context_deleter;
}

void *socket_getcontext(socket_t *self)
{
    return self->context;
}
