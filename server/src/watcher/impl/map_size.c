/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"
#include "watcher_handler.h"

#include "server.h"

#include "hexagon/util/c.h"

void game_watcher_cmd_map_size(UNUSED game_watcher_t *self, csocket_t *client,
    UNUSED list_t *args)
{
    server_t *server = server_get();
    game_t *game = server->game;

    SERVER_LOG(debug, "Map size requested by client %s",
        SOCKET_GETSTRADDR(client));
    csocket_printf(client, "msz %d %d\n", game->width, game->height);
}
