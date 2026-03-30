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
#include "team.h"

#include "hexagon/util/c.h"

void game_watcher_cmd_get_team_names(UNUSED game_watcher_t *self,
    csocket_t *client, UNUSED list_t *args)
{
    server_t *server = server_get();
    list_t *teams = server->game->teams;
    game_team_t *team;

    for (list_node_t *node = teams->first; node; node = node->next) {
        team = node->value;
        csocket_printf(client, "tna %s\n", team->name);
    }
    SERVER_LOG(trace, "Sent %d team names to client %s",
        list_len(teams), SOCKET_GETSTRADDR(client));
}
