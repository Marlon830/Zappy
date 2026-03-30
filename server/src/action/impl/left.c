/*
** EPITECH PROJECT, 2024
** left
** File description:
** file for left functions
*/

#include "server.h"

#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

void game_action_left(
    UNUSED game_t *game, game_player_t *self, UNUSED char *arg)
{
    vec2i_t tmp = {0};

    tmp.x = self->dir.y;
    tmp.y = -self->dir.x;
    self->dir = tmp;
    csocket_writeln(self->client, "ok");
    SERVER_BCWF(FUNC &game_watcher_send_position, self);
    SERVER_LOG(info, "Player #%d turned left", self->id);
}
