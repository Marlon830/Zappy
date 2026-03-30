/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"

#include "server.h"
#include "game.h"

#include "hexagon/util/mem.h"

bool game_watcher_send_map_tile(csocket_t *client, vec2i_t pos)
{
    server_t *server = server_get();
    game_t *game = server->game;
    game_tile_t *tile = game_map_get_at(game, pos);

    if (!tile) {
        SERVER_LOG(debug, "Client %s attempted to get tile %d %d, but getter "
            "returned NULL", SOCKET_GETSTRADDR(client), pos.x, pos.y);
        csocket_writeln(client, "sbp");
        return false;
    }
    csocket_printf(client, "bct %d %d", pos.x, pos.y);
    for (size_t i = 0; i < ARRAY_SIZE(tile->items); i++)
        csocket_printf(client, " %d", tile->items[i]);
    csocket_writeln(client, "");
    return true;
}

void game_watcher_send_position(csocket_t *client, game_player_t *player)
{
    server_t *server = server_get();
    game_t *game = server->game;

    csocket_printf(client, "ppo %s%d %d %d %d\n", GAME_SHITTYGUI(game),
        player->id, player->pos.x, player->pos.y, game_dir2int(player->dir));
}

void game_watcher_send_player_inventory(csocket_t *client,
    game_player_t *player)
{
    server_t *server = server_get();
    game_t *game = server->game;

    csocket_printf(client, "pin %s%d %d %d", GAME_SHITTYGUI(game), player->id,
        player->pos.x, player->pos.y);
    for (size_t i = 0; i < ARRAY_SIZE(player->inv.items); i++) {
        csocket_printf(client, " %d",
            player->inv.items[i] / (1 + ((i == RESOURCE_FOOD) * 125)));
    }
    csocket_writeln(client, "");
}

void game_watcher_send_player_level(csocket_t *client, game_player_t *player)
{
    server_t *server = server_get();
    game_t *game = server->game;

    csocket_printf(client, "plv %s%d %d\n", GAME_SHITTYGUI(game),
        player->id, player->level);
}
