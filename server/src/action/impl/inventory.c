/*
** EPITECH PROJECT, 2024
** inventory
** File description:
** file for inventory functions
*/

#include "server.h"

#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

void game_action_inventory(
    UNUSED game_t *game, game_player_t *self, UNUSED char *arg)
{
    csocket_printf(self->client, "[food %d, linemate %d, deraumere %d, "
        "sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        self->inv.food / 126, self->inv.linemate, self->inv.deraumere,
        self->inv.sibur, self->inv.mendiane, self->inv.phiras,
        self->inv.thystame);
    SERVER_LOG(info, "Sent inventory to player #%d", self->id);
}
