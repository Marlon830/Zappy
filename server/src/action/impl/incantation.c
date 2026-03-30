/*
** EPITECH PROJECT, 2024
** incantation
** File description:
** file for incantation functions
*/

#include <stdbool.h>
#include "server.h"

#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

static void game_start_incantation(
    game_t *game, game_player_t *self, list_t *ids)
{
    game_action_incantation_t *incantation = game_action_incantation_new();
    game_player_t *player;

    for (list_node_t *node = game->players->first; node; node = node->next) {
        player = node->value;
        if (player->pos.x != self->pos.x || player->pos.y != self->pos.y ||
            player->level != self->level)
            continue;
        list_append(incantation->players, player);
        player->incantation = true;
        list_append(ids, &player->id);
        csocket_writeln(player->client, "Elevation underway");
    }
    list_append(game->incantations, incantation);
}

void game_action_incantation(
    game_t *game, game_player_t *self, UNUSED char *arg)
{
    list_t *ids = list_new();

    if (!game_action_incantation_check_reqs(game, self)) {
        csocket_writeln(self->client, "ko");
        list_delete(ids);
        return;
    }
    game_start_incantation(game, self, ids);
    SERVER_BCW("pic %d %d %d", self->pos.x, self->pos.y, self->level);
    for (list_node_t *node = ids->first; node; node = node->next)
        SERVER_BCW(" %s%d", GAME_SHITTYGUI(game), *((int *)node->value));
    SERVER_BCW("\n", "");
    SERVER_LOG(info, "Player #%d started incantation", self->id);
    list_delete(ids);
}
