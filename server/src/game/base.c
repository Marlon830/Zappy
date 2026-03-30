/*
** EPITECH PROJECT, 2024
** base
** File description:
** file for base functions
*/

#include "game.h"
#include "hexagon/util/c.h"
#include "hexagon/util/mem.h"

game_t *game_new(void)
{
    game_t *game = mem_alloc(sizeof(game_t));

    game->width = 10;
    game->height = 10;
    game->map = NULL;
    game->sync_mode = GAME_SYNC_ASYNC;
    game->shitty_gui = false;
    game->tick = 0;
    game->teams = list_new();
    game->players = list_new();
    game->eggs = list_new();
    game->incantations = list_new();
    game->resources = (game_inventory_t){0};
    return game;
}

void game_delete(game_t *self)
{
    list_foreach(self->teams, FUNC &team_delete);
    list_delete(self->teams);
    list_foreach(self->players, FUNC &game_player_delete);
    list_delete(self->players);
    list_foreach(self->eggs, FUNC &game_player_delete);
    list_delete(self->eggs);
    list_foreach(self->incantations, FUNC &game_action_incantation_delete);
    list_delete(self->incantations);
    if (self->map)
        mem_free(self->map);
    mem_free(self);
}
