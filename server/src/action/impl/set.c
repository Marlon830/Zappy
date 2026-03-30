/*
** EPITECH PROJECT, 2024
** set
** File description:
** file for set functions
*/

#include "server.h"

#include "action.h"
#include "player.h"
#include "game.h"

void game_action_set(game_t *game, game_player_t *self, char *arg)
{
    game_resource_t resource = game_get_resource(arg);
    int quantity = resource == RESOURCE_FOOD ? 126 : 1;

    if (resource == RESOURCE_UNKNOWN || self->inv.items[resource] < quantity) {
        csocket_writeln(self->client, "ko");
        return;
    }
    game_map_add_at(game, self->pos, resource, 1);
    self->inv.items[resource] -= quantity;
    csocket_writeln(self->client, "ok");
    SERVER_BCW("pdr %s%d %d\n", GAME_SHITTYGUI(game), self->id, resource);
    SERVER_LOG(info, "Player #%d set %s", self->id,
        game_resource_name(resource));
}
