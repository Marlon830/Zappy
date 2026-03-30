/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "client.h"
#include "server.h"
#include "team.h"

#include "hexagon/net/csocket.h"

#include <assert.h>

static void client_as_player_notify(client_t *self, csocket_t *client_socket)
{
    server_t *server = server_get();
    game_team_t *team = self->player->team;
    game_t *game = server->game;

    csocket_printf(client_socket, "%d\n%d %d\n", game_count_eggs(game, team),
        server->game->width, server->game->height);
    SERVER_BCW("pnw %s%d %d %d %d %d %s\n", GAME_SHITTYGUI(game),
        self->player->id, self->player->pos.x, self->player->pos.y,
        game_dir2int(self->player->dir), self->player->level,
        self->player->team->name);
    SERVER_BCW("ebo %s%d\n", GAME_SHITTYGUI(game), self->player->id);
    SERVER_BCWF(FUNC &game_watcher_send_player_inventory, self->player);
}

bool client_as_player(client_t *self, const char *team_name,
    csocket_t *client_socket)
{
    server_t *server = server_get();
    game_team_t *team;
    game_player_t *player;

    assert(self->type == CLIENTTYPE_UNKNOWN);
    team = game_team_find(server->game, team_name);
    if (!team)
        return false;
    player = game_find_egg(server->game, team);
    if (!player)
        return false;
    team->current_players++;
    self->type = CLIENTTYPE_PLAYER;
    self->player = player;
    self->player->client = client_socket;
    list_append(server->game->players, self->player);
    client_as_player_notify(self, client_socket);
    SERVER_LOG(info, "Client %s joined team %s",
        SOCKET_GETSTRADDR(client_socket), team_name);
    return true;
}

game_player_t *client_player(client_t *self)
{
    assert(self->type == CLIENTTYPE_PLAYER);
    return self->player;
}
