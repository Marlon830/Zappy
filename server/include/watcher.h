/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#pragma once

#include "game.h"
#include "math.h"

#include "hexagon/net/csocket.h"

#include "hexagon/util/list.h"

#include <stdbool.h>

typedef struct game_watcher_s {

} game_watcher_t;

typedef struct game_watcher_cmd_s {
    const char *name;
    int arg_count;
    void (*handler)(game_watcher_t *self, csocket_t *client, list_t *args);
} game_watcher_cmd_t;

extern const game_watcher_cmd_t game_watcher_handlers[];

game_watcher_t *game_watcher_new(void);
void game_watcher_delete(game_watcher_t *self);

bool game_watcher_handle_statement(game_watcher_t *self, csocket_t *client,
    const char *statement);

bool game_watcher_send_map_tile(csocket_t *client, vec2i_t pos);
void game_watcher_send_position(csocket_t *client, game_player_t *player);
void game_watcher_send_player_inventory(csocket_t *client,
    game_player_t *player);
void game_watcher_send_player_level(csocket_t *client, game_player_t *player);
