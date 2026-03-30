/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "client.h"

#include "server.h"

#include "hexagon/util/mem.h"

#include <assert.h>

client_t *client_new(csocket_t *socket)
{
    STRUCT_NEWIN(client, self);
    *self = (client_t) {
        .socket = socket,
        .reader = csocket_linereader_new(socket),
        .type = CLIENTTYPE_UNKNOWN
    };
    csocket_writeln(socket, "WELCOME");
    SERVER_LOG(trace, "Created client context %p", self);
    return self;
}

void client_delete(client_t *self)
{
    server_t *server = server_get();
    size_t i;

    csocket_linereader_delete(self->reader);
    if (self->type == CLIENTTYPE_WATCHER) {
        SERVER_LOG(trace, "Deleted client watcher context %p", self);
        game_watcher_delete(self->watcher);
        mem_free(self);
        return;
    }
    i = list_find(server->game->players, self->player);
    if (i != SIZE_MAX) {
        list_remove(server->game->players, i);
        game_player_delete(self->player);
    }
    mem_free(self);
    SERVER_LOG(trace, "Deleted client player context %p", self);
}
