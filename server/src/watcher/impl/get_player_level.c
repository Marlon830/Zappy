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

void game_watcher_cmd_get_player_level(UNUSED game_watcher_t *self,
    csocket_t *client, list_t *args)
{
    server_t *server = server_get();
    game_t *game = server->game;
    int id = game_get_id(game, list_at(args, 1));
    game_player_t *player = game_player_get(server->game, id);

    if (!player || id < 0) {
        SERVER_LOG(trace, "Invalid player %s%s given from client %s",
            GAME_SHITTYGUI(game), list_at(args, 1), SOCKET_GETSTRADDR(client));
        csocket_writeln(client, "sbp");
        return;
    }
    game_watcher_send_player_level(client, player);
    SERVER_LOG(trace, "Player #%d level sent to client %s",
        player->id, SOCKET_GETSTRADDR(client));
}
