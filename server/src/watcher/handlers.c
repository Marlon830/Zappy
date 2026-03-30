/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"
#include "watcher_handler.h"

const game_watcher_cmd_t game_watcher_handlers[] = {
    {"msz", 0, &game_watcher_cmd_map_size},
    {"bct", 2, &game_watcher_cmd_get_tile_contents},
    {"mct", 0, &game_watcher_cmd_get_map_contents},
    {"tna", 0, &game_watcher_cmd_get_team_names},
    {"ppo", 1, &game_watcher_cmd_get_player_position},
    {"plv", 1, &game_watcher_cmd_get_player_level},
    {"pin", 1, &game_watcher_cmd_get_player_inventory},
    {"sgt", 0, &game_watcher_cmd_get_time_unit},
    {"sst", 1, &game_watcher_cmd_set_time_unit},
    {NULL, 0, NULL}
};
