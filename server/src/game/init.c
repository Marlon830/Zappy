/*
** EPITECH PROJECT, 2024
** init
** File description:
** file for init functions
*/

#include "game.h"

#include <time.h>
#include <stdlib.h>

void game_init(game_t *self, int ppt)
{
    game_team_t *team;
    vec2i_t pos;

    game_generate_map(self);
    for (list_node_t *node = self->teams->first; node; node = node->next) {
        team = node->value;
        team->max_players = ppt;
        for (int i = 0; i < ppt; i++) {
            pos = (vec2i_t){rand() % self->width, rand() % self->height};
            game_add_egg(self, team, pos, game_random_dir());
        }
    }
}
