/*
** EPITECH PROJECT, 2024
** move
** File description:
** file for move functions
*/

#include "server.h"

#include "action.h"
#include "player.h"
#include "game.h"

#include "hexagon/util/c.h"

void game_action_move(game_t *game, game_player_t *self, UNUSED char *arg)
{
    self->pos.x += self->dir.x;
    self->pos.y += self->dir.y;
    self->pos.x %= game->width;
    self->pos.y %= game->height;
    if (self->pos.x < 0)
        self->pos.x += game->width;
    if (self->pos.y < 0)
        self->pos.y += game->height;
    csocket_writeln(self->client, "ok");
    SERVER_BCWF(FUNC &game_watcher_send_position, self);
    SERVER_LOG(info, "Player #%d moved to (%d, %d)", self->id,
        self->pos.x, self->pos.y);
}
