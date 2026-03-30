/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#pragma once

#include "watcher.h"

void game_watcher_cmd_map_size(game_watcher_t *self, csocket_t *client,
    list_t *args);
void game_watcher_cmd_get_tile_contents(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_get_map_contents(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_get_team_names(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_get_player_position(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_get_player_level(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_get_player_inventory(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_get_time_unit(game_watcher_t *self,
    csocket_t *client, list_t *args);
void game_watcher_cmd_set_time_unit(game_watcher_t *self,
    csocket_t *client, list_t *args);
