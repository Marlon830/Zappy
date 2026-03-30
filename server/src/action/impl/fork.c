/*
** EPITECH PROJECT, 2024
** fork
** File description:
** file for fork functions
*/

#include "server.h"

#include "action.h"
#include "player.h"
#include "game.h"

#include "hexagon/util/c.h"

void game_action_fork(game_t *game, game_player_t *self, UNUSED char *arg)
{
    game_player_t *egg = game_add_egg(game, self->team, self->pos, self->dir);

    csocket_writeln(self->client, "ok");
    SERVER_BCW("enw %s%d %s%d %d %d\n", GAME_SHITTYGUI(game),
        egg->id, GAME_SHITTYGUI(game), self->id, self->pos.x, self->pos.y);
    SERVER_LOG(debug, "Player #%d from team `%s` forked an egg",
        self->id, self->team->name);
}
