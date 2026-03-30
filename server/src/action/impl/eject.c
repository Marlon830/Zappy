/*
** EPITECH PROJECT, 2024
** eject
** File description:
** file for eject functions
*/

#include "game.h"
#include "server.h"

#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

static int calculate_direction(vec2i_t sdir, vec2i_t pdir)
{
    if (sdir.x == pdir.x && sdir.y == pdir.y)
        return 5;
    if (sdir.x == pdir.y && sdir.y == -pdir.x)
        return 3;
    if (sdir.x == -pdir.y && sdir.y == pdir.x)
        return 7;
    if (sdir.x == -pdir.x && sdir.y == -pdir.y)
        return 1;
    return 0;
}

static bool eject_players(game_t *game, game_player_t *self)
{
    game_player_t *player;
    bool pushed = false;
    int direction;

    for (list_node_t *node = game->players->first; node; node = node->next) {
        player = node->value;
        if (player == self || player->pos.x != self->pos.x ||
            player->pos.y != self->pos.y)
            continue;
        player->pos.x += self->dir.x;
        player->pos.y += self->dir.y;
        direction = calculate_direction(self->dir, player->dir);
        csocket_printf(player->client, "eject: %d\n", direction);
        SERVER_BCW("pex %s%d\n", GAME_SHITTYGUI(game), player->id);
        pushed = true;
    }
    return pushed;
}

static bool destroy_eggs(game_t *game, game_player_t *self)
{
    game_player_t *egg;
    list_node_t *tmp;
    bool pushed = false;

    for (list_node_t *node = game->eggs->first; node; node = tmp) {
        egg = node->value;
        tmp = node->next;
        if (egg->pos.x != self->pos.x || egg->pos.y != self->pos.y)
            continue;
        list_remove_node(game->eggs, node);
        SERVER_BCW("edi %s%d\n", GAME_SHITTYGUI(game), egg->id);
        pushed = true;
    }
    return pushed;
}

void game_action_eject(game_t *game, game_player_t *self, UNUSED char *arg)
{
    bool pushed = eject_players(game, self) || destroy_eggs(game, self);

    csocket_writeln(self->client, pushed ? "ok" : "ko");
    if (pushed)
        SERVER_LOG(info, "Player #%d ejected players", self->id);
}
