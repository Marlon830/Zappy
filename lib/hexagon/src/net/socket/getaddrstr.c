/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/socket.h"

#include "hexagon/util/mem.h"

#include <arpa/inet.h>

#include <assert.h>
#include <stdio.h>

const char *socket_getstraddr(socket_t *self)
{
    static char addr_str[SOCKET_FULLADDRSTRLEN + 1];

    snprintf(addr_str, ARRAY_SIZE(addr_str), "%s:%hu",
        socket_getipaddr(self), socket_getport(self));
    return addr_str;
}
