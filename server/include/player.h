/*
** EPITECH PROJECT, 2024
** player
** File description:
** file for player functions
*/

#pragma once

#include "action.h"
#include "math.h"
#include "team.h"

#include "hexagon/net/csocket.h"

#include "hexagon/util/list.h"

typedef enum game_resource_e {
    RESOURCE_UNKNOWN = -1,
    RESOURCE_FOOD,
    RESOURCE_LINEMATE,
    RESOURCE_DERAUMERE,
    RESOURCE_SIBUR,
    RESOURCE_MENDIANE,
    RESOURCE_PHIRAS,
    RESOURCE_THYSTAME,
    RESOURCE_COUNT
} game_resource_t;

typedef union game_inventory_u {
    int items[7];
    struct {
        int food;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
    };
} game_inventory_t;

typedef struct game_player_s {
    int id;
    game_team_t *team;
    bool incantation;
    uint8_t level;
    vec2i_t pos;
    vec2i_t dir;
    list_t *actions;
    game_inventory_t inv;
    csocket_t *client;
} game_player_t;

game_player_t *game_player_new(game_team_t *team, game_t *game,
    csocket_t *client_socket);
void game_player_delete(game_player_t *self);

bool game_player_add_action(game_player_t *self, const char *action);

void game_player_tick(game_t *game, game_player_t *self);
void game_player_kill(game_t *game, game_player_t *self, bool delete_socket);

game_player_t *game_player_get(game_t *game, int id);
