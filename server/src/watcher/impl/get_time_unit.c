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

void game_watcher_cmd_get_time_unit(UNUSED game_watcher_t *self,
    csocket_t *client, UNUSED list_t *args)
{
    server_t *server = server_get();

    csocket_printf(client, "sgt %ld\n", server->freq);
    SERVER_LOG(trace, "Sent game frequency to client %s",
        SOCKET_GETSTRADDR(client));
}
