/*
** EPITECH PROJECT, 2024
** connect_nbr
** File description:
** file for connect nbr functions
*/

#include "server.h"

#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

void game_action_connect_nbr(
    UNUSED game_t *game, game_player_t *self, UNUSED char *arg)
{
    csocket_printf(self->client, "%d\n",
        self->team->max_players - self->team->current_players);
    SERVER_LOG(info, "Sent connect_nbr to player #%d", self->id);
}
