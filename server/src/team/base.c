/*
** EPITECH PROJECT, 2024
** base
** File description:
** file for base functions
*/

#include <stdlib.h>
#include <string.h>

#include "hexagon/util/mem.h"
#include "team.h"

game_team_t *team_new(const char *name)
{
    game_team_t *team = mem_alloc(sizeof(game_team_t));

    team->name = strdup(name);
    team->max_players = 0;
    team->current_players = 0;
    team->max_levels = 0;
    return team;
}

void team_delete(game_team_t *self)
{
    free(self->name);
    mem_free(self);
}
