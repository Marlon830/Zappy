/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "client.h"

#include "player.h"
#include "server.h"

#include <assert.h>

static void client_as_watcher_announce(client_t *self)
{
    server_t *server = server_get();
    game_t *game = server->game;
    game_player_t *player = NULL;

    for (list_node_t *node = server->game->eggs->first; node;
        node = node->next) {
        player = node->value;
        csocket_printf(self->socket, "enw %s%d %s-1 %d %d\n",
            GAME_SHITTYGUI(game), player->id,
            GAME_SHITTYGUI(game), player->pos.x, player->pos.y);
    }
    for (list_node_t *node = server->game->players->first; node;
        node = node->next) {
        player = node->value;
        csocket_printf(self->socket, "pnw %s%d %d %d %d %d %s\n",
            GAME_SHITTYGUI(game), player->id, player->pos.x, player->pos.y,
            game_dir2int(player->dir), player->level, player->team->name);
        game_watcher_send_player_inventory(self->socket, player);
    }
}

void client_as_watcher(client_t *self)
{
    server_t *server = server_get();

    assert(self->type == CLIENTTYPE_UNKNOWN);
    self->type = CLIENTTYPE_WATCHER;
    self->watcher = game_watcher_new();
    if (server->game->sync_mode != GAME_SYNC_ASYNC)
        return;
    game_watcher_handle_statement(self->watcher, self->socket, "msz");
    game_watcher_handle_statement(self->watcher, self->socket, "sgt");
    game_watcher_handle_statement(self->watcher, self->socket, "mct");
    game_watcher_handle_statement(self->watcher, self->socket, "tna");
    client_as_watcher_announce(self);
}

game_watcher_t *client_watcher(client_t *self)
{
    assert(self->type == CLIENTTYPE_WATCHER);
    return self->watcher;
}
