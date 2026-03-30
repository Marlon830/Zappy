/*
** EPITECH PROJECT, 2024
** manage
** File description:
** file for manage functions
*/

#include "game.h"

game_player_t *game_add_egg(
    game_t *self, game_team_t *team, vec2i_t pos, vec2i_t dir)
{
    game_player_t *player = game_player_new(team, self, NULL);

    player->pos = pos;
    player->dir = dir;
    list_append(self->eggs, player);
    return player;
}

game_player_t *game_find_egg(game_t *self, game_team_t *team)
{
    game_player_t *player;
    list_node_t *next_node;

    for (list_node_t *node = self->eggs->first; node; node = next_node) {
        next_node = node->next;
        player = node->value;
        if (player->team == team) {
            list_remove_node(self->eggs, node);
            return player;
        }
    }
    return NULL;
}

size_t game_count_eggs(game_t *self, game_team_t *team)
{
    size_t count = 0;
    game_player_t *player;

    for (list_node_t *node = self->eggs->first; node; node = node->next) {
        player = node->value;
        if (player->team == team)
            count++;
    }
    return count;
}
