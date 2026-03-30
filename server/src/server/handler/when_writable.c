/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server_handler.h"
#include "server.h"

#include "hexagon/util/c.h"

void server_handler_when_writable(UNUSED server_t *server,
    UNUSED ssocket_t *server_socket, csocket_t *client_socket)
{
    SERVER_LOG(trace, "Flushing %zu bytes to client %s",
        csocket_getout(client_socket), SOCKET_GETSTRADDR(client_socket));
}
