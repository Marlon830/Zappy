/*
** EPITECH PROJECT, 2024
** map
** File description:
** file for map functions
*/

#include "game.h"

game_tile_t *game_map_get_at(game_t *self, vec2i_t pos)
{
    int x = pos.x % self->width;
    int y = pos.y % self->height;

    if (x < 0)
        x += self->width;
    if (y < 0)
        y += self->height;
    return &self->map[y * self->width + x];
}

list_t *game_map_get_players_at(game_t *self, vec2i_t pos)
{
    list_t *players = list_new();
    game_player_t *player;

    for (list_node_t *node = self->players->first; node; node = node->next) {
        player = node->value;
        if (player->pos.x == pos.x && player->pos.y == pos.y)
            list_append(players, player);
    }
    return players;
}

void game_map_remove_at(
    game_t *self, vec2i_t pos, game_resource_t type, int amount)
{
    game_tile_t *tile = game_map_get_at(self, pos);

    tile->items[type] -= amount;
    self->resources.items[type] -= amount;
}

void game_map_add_at(
    game_t *self, vec2i_t pos, game_resource_t type, int amount)
{
    game_tile_t *tile = game_map_get_at(self, pos);

    tile->items[type] += amount;
    self->resources.items[type] += amount;
}
