/*
** EPITECH PROJECT, 2024
** incantation
** File description:
** file for incantation functions
*/

#include "server.h"
#include "action.h"
#include "game.h"

#include "hexagon/util/mem.h"

const game_action_incantation_req_t game_action_incantation_reqs[] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1},
    {9, 9, 9, 9, 9, 9, 9}
};

bool game_action_incantation_check_reqs(game_t *game, game_player_t *self)
{
    const game_action_incantation_req_t *req =
        &game_action_incantation_reqs[self->level - 1];
    game_inventory_t *tile = game_map_get_at(game, self->pos);
    game_player_t *player;
    int players = 0;

    if (self->level >= 8)
        return false;
    for (list_node_t *node = game->players->first; node; node = node->next) {
        player = node->value;
        if (player->pos.x == self->pos.x && player->pos.y == self->pos.y &&
            player->level == self->level)
            players++;
    }
    return players >= req->players && tile->linemate >= req->linemate &&
        tile->deraumere >= req->deraumere && tile->sibur >= req->sibur &&
        tile->mendiane >= req->mendiane && tile->phiras >= req->phiras &&
        tile->thystame >= req->thystame;
}

game_action_incantation_t *game_action_incantation_new(void)
{
    STRUCT_NEWIN(game_action_incantation, incantation);
    incantation->players = list_new();
    incantation->tick = 300;
    return incantation;
}

void game_action_incantation_delete(game_action_incantation_t *self)
{
    list_delete(self->players);
    mem_free(self);
}

static void game_action_incantation_sendlevel(game_t *game,
    game_player_t *player)
{
    if (game->sync_mode == GAME_SYNC_ASYNC)
        SERVER_BCWF(FUNC &game_watcher_send_player_level, player);
}

void game_action_incantation_execute(
    game_t *game, game_action_incantation_t *self)
{
    game_player_t *player = self->players->first->value;
    bool success = game_action_incantation_check_reqs(game, player);

    if (success)
        game_action_incantation_consume_reqs(game, player);
    for (list_node_t *node = self->players->first; node; node = node->next) {
        player = node->value;
        player->incantation = false;
        player->level += success;
        if (success) {
            csocket_printf(player->client, "Current level: %d\n",
                player->level);
            game_action_incantation_sendlevel(game, player);
        } else
            csocket_writeln(player->client, "ko");
        if (player->level == 8)
            player->team->max_levels++;
    }
    SERVER_BCW("pie %d %d %d\n", player->pos.x, player->pos.y, success);
    SERVER_LOG(info, "Incantation finished");
}

void game_action_incantation_consume_reqs(game_t *game, game_player_t *self)
{
    game_action_incantation_req_t req =
        game_action_incantation_reqs[self->level - 1];

    game_map_remove_at(game, self->pos, RESOURCE_LINEMATE, req.linemate);
    game_map_remove_at(game, self->pos, RESOURCE_DERAUMERE, req.deraumere);
    game_map_remove_at(game, self->pos, RESOURCE_SIBUR, req.sibur);
    game_map_remove_at(game, self->pos, RESOURCE_MENDIANE, req.mendiane);
    game_map_remove_at(game, self->pos, RESOURCE_PHIRAS, req.phiras);
    game_map_remove_at(game, self->pos, RESOURCE_THYSTAME, req.thystame);
}
