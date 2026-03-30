/*
** EPITECH PROJECT, 2024
** util
** File description:
** file for util functions
*/

#include "game.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <inttypes.h>

vec2i_t game_random_dir(void)
{
    int dir;

    dir = rand() % 4;
    switch (dir) {
        case 0:
            return (vec2i_t){0, 1};
        case 1:
            return (vec2i_t){0, -1};
        case 2:
            return (vec2i_t){1, 0};
        case 3:
            return (vec2i_t){-1, 0};
        default:
            return (vec2i_t){69, 42};
    }
}

int game_dir2int(vec2i_t dir)
{
    static const struct {
        vec2i_t dir;
        int value;
    } dirs[] = {
        {{0, -1}, 1},
        {{1, 0}, 2},
        {{0, 1}, 3},
        {{-1, 0}, 4}
    };

    for (int i = 0; i < 4; i++)
        if (dirs[i].dir.x == dir.x && dirs[i].dir.y == dir.y)
            return dirs[i].value;
    assert(false);
    return 0;
}

int game_get_id(game_t *self, const char *arg)
{
    const char *arg_ptr;
    int id;
    game_player_t *player;

    if (!self->shitty_gui) {
        if (*arg != '#')
            return -1;
        arg++;
    }
    if (!(*arg >= '0' && *arg <= '9'))
        return -1;
    id = strtoumax(arg, (char **) &arg_ptr, 10);
    if (*arg_ptr != '\0')
        return -1;
    for (list_node_t *node = self->players->first; node; node = node->next) {
        player = node->value;
        if (player->id == id)
            return id;
    }
    return -1;
}

game_resource_t game_get_resource(const char *str)
{
    if (str == NULL)
        return RESOURCE_UNKNOWN;
    if (strcmp(str, "food") == 0)
        return RESOURCE_FOOD;
    if (strcmp(str, "linemate") == 0)
        return RESOURCE_LINEMATE;
    if (strcmp(str, "deraumere") == 0)
        return RESOURCE_DERAUMERE;
    if (strcmp(str, "sibur") == 0)
        return RESOURCE_SIBUR;
    if (strcmp(str, "mendiane") == 0)
        return RESOURCE_MENDIANE;
    if (strcmp(str, "phiras") == 0)
        return RESOURCE_PHIRAS;
    if (strcmp(str, "thystame") == 0)
        return RESOURCE_THYSTAME;
    return RESOURCE_UNKNOWN;
}

const char *game_resource_name(game_resource_t type)
{
    switch (type) {
        case RESOURCE_FOOD:
            return "food";
        case RESOURCE_LINEMATE:
            return "linemate";
        case RESOURCE_DERAUMERE:
            return "deraumere";
        case RESOURCE_SIBUR:
            return "sibur";
        case RESOURCE_MENDIANE:
            return "mendiane";
        case RESOURCE_PHIRAS:
            return "phiras";
        case RESOURCE_THYSTAME:
            return "thystame";
        default:
            return "unknown";
    }
}
