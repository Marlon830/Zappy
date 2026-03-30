/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/socket.h"

uint16_t socket_getport(socket_t *self)
{
    return self->port;
}
