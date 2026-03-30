/*
** EPITECH PROJECT, 2024
** game
** File description:
** file for game functions
*/

#pragma once

#include "math.h"
#include "player.h"
#include "team.h"

#include "hexagon/net/csocket.h"

#include "hexagon/util/list.h"

typedef enum game_sync_mode_e {
    GAME_SYNC_ASYNC,
    GAME_SYNC_EXPLICIT,
} game_sync_mode_t;

typedef game_inventory_t game_tile_t;
typedef game_tile_t *game_map_t;

typedef struct game_s {
    int width;
    int height;
    game_map_t map;
    game_sync_mode_t sync_mode;
    bool shitty_gui;
    bool ended;

    long tick;

    list_t *teams;
    list_t *players;
    list_t *eggs;
    list_t *incantations;
    game_inventory_t resources;
} game_t;

#define GAME_SHITTYGUI(self) ((self)->shitty_gui ? "" : "#")

game_t *game_new(void);
void game_delete(game_t *self);

void game_init(game_t *self, int ppt);
void game_generate_map(game_t *self);
void game_generate_resources(game_t *self);
void game_generate_resource(
    game_t *self, game_resource_t type, double density);
void game_tick(game_t *self);

game_player_t *game_add_egg(
    game_t *self, game_team_t *team, vec2i_t pos, vec2i_t dir);
game_player_t *game_find_egg(game_t *self, game_team_t *team);
size_t game_count_eggs(game_t *self, game_team_t *team);

game_player_t *game_join(game_t *self, csocket_t *client, char *team);

game_tile_t *game_map_get_at(game_t *self, vec2i_t pos);
list_t *game_map_get_players_at(game_t *self, vec2i_t pos);
void game_map_remove_at(
    game_t *self, vec2i_t pos, game_resource_t type, int amount);
void game_map_add_at(
    game_t *self, vec2i_t pos, game_resource_t type, int amount);

vec2i_t game_random_dir(void);
int game_dir2int(vec2i_t dir);
int game_get_id(game_t *self, const char *arg);

game_resource_t game_get_resource(const char *str);
const char *game_resource_name(game_resource_t type);
