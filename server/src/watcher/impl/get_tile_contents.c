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
#include <inttypes.h>

void game_watcher_cmd_get_tile_contents(UNUSED game_watcher_t *self,
    csocket_t *client, list_t *args)
{
    server_t *server = server_get();
    const char *x_ptr;
    const char *y_ptr;
    unsigned int x = strtoumax(list_at(args, 1), (char **) &x_ptr, 10);
    unsigned int y = strtoumax(list_at(args, 2), (char **) &y_ptr, 10);
    vec2i_t pos = {x, y};

    if (*x_ptr || *y_ptr ||
        x >= 1u * server->game->width || y >= 1u * server->game->height) {
        SERVER_LOG(trace, "Invalid tile position (%s, %s) given from client "
            "%s", list_at(args, 1), list_at(args, 2),
            SOCKET_GETSTRADDR(client));
        csocket_writeln(client, "sbp");
        return;
    }
    game_watcher_send_map_tile(client, pos);
    SERVER_LOG(trace, "Sent map tile (%d, %d) to client %s",
        pos.x, pos.y, SOCKET_GETSTRADDR(client));
}
