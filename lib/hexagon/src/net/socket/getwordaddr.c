/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/socket.h"

#include <arpa/inet.h>

void socket_getwordaddr(socket_t *self, uint8_t addr[4])
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    getsockname(self->fd, (struct sockaddr *) &sin, &len);
    *((uint32_t *) addr) = htonl(sin.sin_addr.s_addr);
}
