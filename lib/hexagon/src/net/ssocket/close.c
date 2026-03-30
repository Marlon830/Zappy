/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/ssocket.h"
#include "hexagon/net/csocket.h"

#include <assert.h>
#include <limits.h>

void ssocket_close(ssocket_t *self, csocket_t *client_socket)
{
    size_t i = list_find(self->clients, client_socket);

    if (i == ULONG_MAX)
        return;
    list_remove(self->clients, i);
    csocket_delete(client_socket);
}
