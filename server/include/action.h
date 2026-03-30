/*
** EPITECH PROJECT, 2024
** action
** File description:
** file for action functions
*/

#pragma once

#include <stdbool.h>
#include "hexagon/util/list.h"

typedef struct game_s game_t;
typedef struct game_player_s game_player_t;

typedef void (*game_action_func_t)(game_t *, game_player_t *, char *);

typedef struct game_action_info_s {
    char *name;
    int len;
    int delay;
    int args;
    game_action_func_t callback;
} game_action_info_t;

typedef struct game_action_s {
    game_action_func_t callback;
    int tick;
    char *arg;
} game_action_t;

typedef struct game_action_incantation_req_s {
    int players;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} game_action_incantation_req_t;

typedef struct game_action_incantation_s {
    list_t *players;
    int tick;
} game_action_incantation_t;

game_action_t *game_action_new(const char *action);
void game_action_delete(game_action_t *self);

void game_action_move(game_t *game, game_player_t *player, char *arg);
void game_action_right(game_t *game, game_player_t *player, char *arg);
void game_action_left(game_t *game, game_player_t *player, char *arg);
void game_action_look(game_t *game, game_player_t *player, char *arg);
void game_action_inventory(game_t *game, game_player_t *player, char *arg);
void game_action_broadcast(game_t *game, game_player_t *player, char *msg);
void game_action_connect_nbr(game_t *game, game_player_t *player, char *arg);
void game_action_fork(game_t *game, game_player_t *player, char *arg);
void game_action_eject(game_t *game, game_player_t *player, char *arg);
void game_action_take(game_t *game, game_player_t *player, char *item);
void game_action_set(game_t *game, game_player_t *player, char *item);
void game_action_incantation(game_t *game, game_player_t *player, char *arg);

bool game_action_incantation_check_reqs(game_t *game, game_player_t *self);
game_action_incantation_t *game_action_incantation_new(void);
void game_action_incantation_delete(game_action_incantation_t *self);
void game_action_incantation_execute(game_t *game,
    game_action_incantation_t *self);
void game_action_incantation_consume_reqs(game_t *game, game_player_t *self);

/*
 * If you don't like ternary operators, you are an idiot.
 *
 * Since the coding style prevents me from using ternary operators in for
 * loops, I hope you have got the conclusion.
 */
#define ACTLOOK_INIT reverse_dir ? lvl : -lvl
#define ACTLOOK_COND reverse_dir ? off >= -lvl : off <= lvl
#define ACTLOOK_INC reverse_dir ? off-- : off++

extern const game_action_info_t game_actions_info[];
extern const game_action_incantation_req_t game_incantation_reqs[];
