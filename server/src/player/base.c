/*
** EPITECH PROJECT, 2024
** base
** File description:
** file for base functions
*/

#include "player.h"

#include "server.h"

#include "hexagon/util/c.h"
#include "hexagon/util/mem.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

game_player_t *game_player_new(game_team_t *team, game_t *game,
    csocket_t *client_socket)
{
    game_player_t *player = mem_alloc(sizeof(game_player_t));
    static int i = 0;

    player->id = i;
    i++;
    player->level = 1;
    player->team = team;
    player->client = client_socket;
    player->incantation = false;
    player->actions = list_new();
    player->pos = (vec2i_t){rand() % game->width, rand() % game->height};
    player->dir = game_random_dir();
    player->inv = (game_inventory_t){{1260, 0, 0, 0, 0, 0, 0}};
    return player;
}

void game_player_delete(game_player_t *self)
{
    list_foreach(self->actions, FUNC &game_action_delete);
    list_delete(self->actions);
    mem_free(self);
}
