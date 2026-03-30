/*
** EPITECH PROJECT, 2024
** tick
** File description:
** file for tick functions
*/

#include "player.h"
#include "game.h"
#include "server.h"
#include "watcher.h"

static void game_player_tick_send_inventory(game_t *game, game_player_t *self)
{
    if (game->sync_mode != GAME_SYNC_ASYNC ||
        self->inv.food % 126 != 0)
        return;
    SERVER_BCWF(FUNC &game_watcher_send_player_inventory, self);
}

void game_player_tick(game_t *game, game_player_t *self)
{
    game_action_t *action;

    game_player_tick_send_inventory(game, self);
    self->inv.food -= 1;
    if (self->inv.food <= 0)
        return game_player_kill(game, self, true);
    if (!self->actions->size || self->incantation)
        return;
    action = self->actions->first->value;
    if (action->tick == 42 && action->callback == game_action_fork)
        SERVER_BCW("pfk %s%d\n", GAME_SHITTYGUI(game), self->id);
    if (action->tick > 0) {
        action->tick--;
        return;
    }
    SERVER_LOG(debug, "Executing action %p for player %s", action->callback,
        SOCKET_GETSTRADDR(self->client));
    action->callback(game, self, action->arg);
    game_action_delete(action);
    list_remove(self->actions, 0);
}
