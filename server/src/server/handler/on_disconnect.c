/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server_handler.h"

#include "client.h"

#include "hexagon/util/c.h"

void server_handler_on_disconnect(
    server_t *server, UNUSED ssocket_t *server_socket,
    csocket_t *client_socket)
{
    client_t *client = SOCKET_GETCONTEXT(client_socket, client);

    SERVER_LOG(info, "Client %s disconnected from server",
        SOCKET_GETSTRADDR(client_socket));
    if (client->type == CLIENTTYPE_PLAYER)
        game_player_kill(server->game, client_player(client), false);
}
