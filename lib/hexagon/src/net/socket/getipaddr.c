/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/socket.h"

const char *socket_getipaddr(socket_t *self)
{
    return self->ip_addr;
}
