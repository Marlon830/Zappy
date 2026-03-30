/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"

#include "hexagon/util/mem.h"

game_watcher_t *game_watcher_new(void)
{
    STRUCT_NEWIN(game_watcher, self);
    return self;
}

void game_watcher_delete(game_watcher_t *self)
{
    mem_free(self);
}
