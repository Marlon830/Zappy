/*
** EPITECH PROJECT, 2024
** action
** File description:
** file for action functions
*/

#include "action.h"
#include "player.h"
#include "game.h"

bool game_player_add_action(game_player_t *self, const char *action)
{
    game_action_t *game_action;

    if (self->actions->size >= 10)
        return false;
    game_action = game_action_new(action);
    if (!game_action)
        return false;
    if (!game_action->callback) {
        game_action_delete(game_action);
        return false;
    }
    list_append(self->actions, game_action);
    return true;
}
