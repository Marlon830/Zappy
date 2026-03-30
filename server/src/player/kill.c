/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "player.h"
#include "server.h"
#include "watcher.h"

void game_player_kill(game_t *game, game_player_t *self, bool delete_socket)
{
    if (self->level == 8)
        self->team->max_levels--;
    self->team->current_players--;
    SERVER_LOG(info, "Player #%d died", self->id);
    csocket_writeln(self->client, "dead");
    SERVER_BCW("pdi %s%d\n", GAME_SHITTYGUI(game), self->id);
    if (delete_socket)
        ssocket_close(server_get()->socket, self->client);
}
