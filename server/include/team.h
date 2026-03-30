/*
** EPITECH PROJECT, 2024
** team
** File description:
** file for team functions
*/

#pragma once

#include "hexagon/util/c.h"

typedef struct game_s game_t;

typedef struct game_team_s {
    char *name;
    int max_players;
    int current_players;
    int max_levels;
} game_team_t;

game_team_t *team_new(const char *name);
void team_delete(game_team_t *self);

game_team_t *game_team_find(game_t *game, const char *name);
