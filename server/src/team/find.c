/*
** EPITECH PROJECT, 2024
** find
** File description:
** file for find functions
*/

#include <string.h>
#include "game.h"
#include "team.h"

game_team_t *game_team_find(game_t *game, const char *name)
{
    game_team_t *team;

    for (list_node_t *node = game->teams->first; node; node = node->next) {
        team = node->value;
        if (strcmp(team->name, name) == 0)
            return team;
    }
    return NULL;
}
