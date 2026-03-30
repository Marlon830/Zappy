/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"
#include "watcher_handler.h"

#include "server.h"
#include "game.h"

#include "hexagon/util/c.h"

#include <assert.h>

void game_watcher_cmd_get_map_contents(UNUSED game_watcher_t *self,
    csocket_t *client, UNUSED list_t *args)
{
    server_t *server = server_get();
    game_t *game = server->game;
    vec2i_t pos;

    for (pos.y = 0; pos.y < game->height; pos.y++)
        for (pos.x = 0; pos.x < game->width; pos.x++)
            game_watcher_send_map_tile(client, pos);
    SERVER_LOG(trace, "Sent map contents (of size %d, %d) to client %s",
        game->width, game->height, SOCKET_GETSTRADDR(client));
}
