/*
** EPITECH PROJECT, 2024
** look
** File description:
** file for look functions
*/

#include "server.h"

#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

#include <stdlib.h>
#include <assert.h>

static void game_action_look_print_tile(game_t *game, game_player_t *self,
    vec2i_t pos)
{
    const char *name;
    game_tile_t *tile = game_map_get_at(game, pos);
    list_t *players = game_map_get_players_at(game, pos);

    for (size_t p = 0; p < players->size; p++)
        csocket_writestr(self->client, " player");
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        name = game_resource_name(i);
        for (int j = 0; j < tile->items[i]; j++)
            csocket_printf(self->client, " %s", name);
    }
    list_delete(players);
}

static void game_action_look_do(game_t *game, game_player_t *self,
    int lvl, int off)
{
    bool reverse_dir = self->dir.x < 0 || self->dir.y > 0;
    vec2i_t pos;

    if (self->dir.x == 0)
        pos = (vec2i_t) {self->pos.x + off, self->pos.y + lvl * self->dir.y};
    else if (self->dir.y == 0)
        pos = (vec2i_t) {self->pos.x + lvl * self->dir.x, self->pos.y + off};
    else
        assert(false);
    SERVER_LOG(debug, "Sending tile info at (%d, %d)", pos.x, pos.y);
    game_action_look_print_tile(game, self, pos);
    if ((!reverse_dir && off < lvl) ||
        (reverse_dir && off > -lvl) ||
        lvl < self->level)
        csocket_writestr(self->client, ",");
}

void game_action_look(game_t *game, game_player_t *self, UNUSED char *arg)
{
    bool reverse_dir = self->dir.x < 0 || self->dir.y > 0;

    csocket_writestr(self->client, "[");
    for (int lvl = 0; lvl <= self->level; lvl++)
        for (int off = ACTLOOK_INIT; ACTLOOK_COND; ACTLOOK_INC)
            game_action_look_do(game, self, lvl, off);
    csocket_writeln(self->client, " ]");
    SERVER_LOG(info, "Player #%d looked from (%d, %d)", self->id,
        self->pos.x, self->pos.y);
}
