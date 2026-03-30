/*
** EPITECH PROJECT, 2024
** player
** File description:
** file for player functions
*/

#include "player.h"

#include "game.h"

game_player_t *game_player_get(game_t *game, int id)
{
    game_player_t *player;

    for (list_node_t *node = game->players->first; node; node = node->next) {
        player = node->value;
        if (player->id == id)
            return player;
    }
    return NULL;
}
