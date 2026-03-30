/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server_handler.h"

#include "client.h"

#include "hexagon/util/c.h"

#include <string.h>

static void (*server_state_handlers[])(
    server_t *server, csocket_t *client_socket, const char *statement
) =
{
    [CLIENTTYPE_UNKNOWN] = &server_handler_when_readable_state_unknown,
    [CLIENTTYPE_PLAYER] = &server_handler_when_readable_state_player,
    [CLIENTTYPE_WATCHER] = &server_handler_when_readable_state_watcher
};

void server_handler_when_readable_state_unknown(
    UNUSED server_t *server, csocket_t *client_socket, const char *statement)
{
    client_t *client = SOCKET_GETCONTEXT(client_socket, client);

    if (strcmp(statement, SERVER_GRAPHIC_TEAMNAME) == 0)
        client_as_watcher(client);
    else if (!client_as_player(client, statement, client_socket)) {
        csocket_writeln(client_socket, "ko");
        SERVER_LOG(warn, "Couldn't assign team '%s' to client %s",
            statement, SOCKET_GETSTRADDR(client_socket));
    }
}

void server_handler_when_readable_state_player(
    UNUSED server_t *server, csocket_t *client_socket, const char *statement)
{
    client_t *client = SOCKET_GETCONTEXT(client_socket, client);
    game_player_t *player = client_player(client);

    SERVER_LOG(debug, "Received statement from game player %s",
        SOCKET_GETSTRADDR(client_socket));
    if (!game_player_add_action(player, statement)) {
        SERVER_LOG(warn, "Could not queue action '%s' sent by game player %s",
            statement, SOCKET_GETSTRADDR(client_socket));
        csocket_writeln(client_socket, "ko");
    }
}

void server_handler_when_readable_state_watcher(
    UNUSED server_t *server, csocket_t *client_socket, const char *statement)
{
    client_t *client = SOCKET_GETCONTEXT(client_socket, client);
    game_watcher_t *watcher = client_watcher(client);

    SERVER_LOG(debug, "Received statement from game watcher %s",
        SOCKET_GETSTRADDR(client_socket));
    if (!game_watcher_handle_statement(watcher, client_socket, statement)) {
        SERVER_LOG(warn, "Statement '%s' sent by game watcher %s is unknown",
            statement, SOCKET_GETSTRADDR(client_socket));
        csocket_writeln(client_socket, "suc");
    }
}

void server_handler_when_readable(
    UNUSED server_t *server, UNUSED ssocket_t *server_socket,
    csocket_t *client_socket
)
{
    client_t *client = SOCKET_GETCONTEXT(client_socket, client);
    const char *statement;

    SERVER_LOG(trace, "Received %zu bytes from client %s",
        csocket_getin(client_socket), SOCKET_GETSTRADDR(client_socket));
    while (true) {
        statement = csocket_linereader_read(client->reader, "\n");
        if (!statement)
            return;
        SERVER_LOG(trace, "Received statement from client %s: '%s'",
            SOCKET_GETSTRADDR(client_socket), statement);
        server_state_handlers[client->type](server, client_socket, statement);
    }
}
