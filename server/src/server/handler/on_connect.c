/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server_handler.h"

#include "client.h"

#include "hexagon/util/c.h"

void server_handler_on_connect(
    UNUSED server_t *server, UNUSED ssocket_t *server_socket,
    csocket_t *client_socket)
{
    SERVER_LOG(info, "Client %s connected to server, initiating context",
        SOCKET_GETSTRADDR(client_socket));
    SOCKET_BINDCONTEXT(client_socket, client_new(client_socket),
        FUNC &client_delete);
}
