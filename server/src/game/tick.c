/*
** EPITECH PROJECT, 2024
** tick
** File description:
** file for tick functions
*/

#include "server.h"

static void game_tick_incantation(game_t *game)
{
    list_node_t *tmp;
    game_action_incantation_t *incantation;

    for (list_node_t *node = game->incantations->first; node;) {
        incantation = node->value;
        tmp = node;
        node = node->next;
        if (incantation->tick > 0) {
            incantation->tick--;
            continue;
        }
        game_action_incantation_execute(game, incantation);
        game_action_incantation_delete(incantation);
        list_remove_node(game->incantations, tmp);
    }
}

static game_team_t *game_finished(game_t *game)
{
    game_team_t *team;

    for (list_node_t *node = game->teams->first; node; node = node->next) {
        team = node->value;
        if (team->max_levels >= 6)
            return team;
    }
    return NULL;
}

static void game_end(game_t *game, game_team_t *team)
{
    SERVER_BCW("seg %s\n", team->name);
    game->ended = true;
}

void game_tick(game_t *game)
{
    list_node_t *next;
    game_team_t *team;

    if (game->ended)
        return;
    game->tick++;
    game_tick_incantation(game);
    for (list_node_t *node = game->players->first; node; node = next) {
        next = node->next;
        game_player_tick(game, node->value);
    }
    team = game_finished(game);
    if (team)
        return game_end(game, team);
    if (game->tick % 20 == 0)
        game_generate_resources(game);
}
