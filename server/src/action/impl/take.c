/*
** EPITECH PROJECT, 2024
** take
** File description:
** file for take functions
*/

#include "server.h"

#include "action.h"
#include "player.h"
#include "game.h"

void game_action_take(game_t *game, game_player_t *self, char *arg)
{
    game_resource_t resource = game_get_resource(arg);
    game_tile_t *tile = game_map_get_at(game, self->pos);

    if (resource == RESOURCE_UNKNOWN || tile->items[resource] <= 0) {
        csocket_writeln(self->client, "ko");
        return;
    }
    game_map_remove_at(game, self->pos, resource, 1);
    self->inv.items[resource] += resource == RESOURCE_FOOD ? 126 : 1;
    csocket_writeln(self->client, "ok");
    SERVER_BCW("pgt %s%d %d\n", GAME_SHITTYGUI(game), self->id, resource);
    SERVER_LOG(info, "Player #%d took %s", self->id,
        game_resource_name(resource));
}
