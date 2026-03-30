/*
** EPITECH PROJECT, 2024
** base
** File description:
** file for base functions
*/

#include <stdlib.h>
#include <string.h>
#include "action.h"

#include "hexagon/util/mem.h"

const game_action_info_t game_action_infos[] = {
    {"Forward", 7, 7, 0, &game_action_move},
    {"Right", 5, 7, 0, &game_action_right},
    {"Left", 4, 7, 0, &game_action_left},
    {"Look", 4, 7, 0, &game_action_look},
    {"Inventory", 9, 1, 0, &game_action_inventory},
    {"Broadcast", 9, 7, 1, &game_action_broadcast},
    {"Connect_nbr", 11, 0, 0, &game_action_connect_nbr},
    {"Fork", 4, 42, 0, &game_action_fork},
    {"Eject", 5, 7, 0, &game_action_eject},
    {"Take", 4, 7, 1, &game_action_take},
    {"Set", 3, 7, 1, &game_action_set},
    {"Incantation", 11, 0, 0, &game_action_incantation}
};

static char *get_arg(const char *action, int len)
{
    size_t n = strlen(action) - len;
    char *arg = mem_alloc(n + 1);

    for (int i = len; action[i]; i++)
        arg[i - len] = action[i];
    arg[n] = '\0';
    return arg;
}

game_action_t *game_action_new(const char *action)
{
    game_action_t *new = mem_alloc(sizeof(game_action_t));

    for (size_t i = 0; i < ARRAY_SIZE(game_action_infos); i++) {
        if (strncmp(action, game_action_infos[i].name,
            game_action_infos[i].len) == 0) {
            new->callback = game_action_infos[i].callback;
            new->tick = game_action_infos[i].delay;
            new->arg = game_action_infos[i].args &&
                action[game_action_infos[i].len] ?
                get_arg(action, game_action_infos[i].len + 1) :
                NULL;
            return new;
        }
    }
    new->callback = NULL;
    new->tick = 0;
    new->arg = NULL;
    return new;
}

void game_action_delete(game_action_t *self)
{
    if (self->arg)
        mem_free(self->arg);
    mem_free(self);
}
