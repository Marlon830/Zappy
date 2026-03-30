/*
** EPITECH PROJECT, 2024
** broadcast
** File description:
** file for broadcast functions
*/

#include "server.h"
#include "action.h"
#include "player.h"

#include "hexagon/util/c.h"

static vec2i_t calc_dist(game_t *game, vec2i_t spos, vec2i_t ppos)
{
    vec2i_t dist;

    dist.x = ppos.x - spos.x;
    dist.y = ppos.y - spos.y;
    if (dist.x > game->width / 2)
        dist.x -= game->width;
    if (dist.x < -game->width / 2)
        dist.x += game->width;
    if (dist.y > game->height / 2)
        dist.y -= game->height;
    if (dist.y < -game->height / 2)
        dist.y += game->height;
    return dist;
}

static int calculate_direction(game_t *game, vec2i_t spos, vec2i_t ppos)
{
    vec2i_t dist = calc_dist(game, spos, ppos);

    if (dist.x == 0 && dist.y == 0)
        return -1;
    if (dist.x == dist.y)
        return (dist.x > 0) ? 2 : 6;
    if (dist.x == -dist.y)
        return (dist.x > 0) ? 4 : 8;
    if (ABS(dist.x) > ABS(dist.y))
        return (dist.x > 0) ? 3 : 7;
    return (dist.y > 0) ? 1 : 5;
}

static int get_direction_offset(vec2i_t dir)
{
    if (dir.x == 1 && dir.y == 0)
        return 2;
    if (dir.x == -1 && dir.y == 0)
        return 6;
    if (dir.x == 0 && dir.y == 1)
        return 4;
    return 0;
}

static int get_final_direction(int direction, vec2i_t dir)
{
    direction = direction == -1 ? -1 :
        (direction + get_direction_offset(dir)) % 8;
    direction = (direction == 0) ? 8 : direction;
    return (direction == -1) ? 0 : direction;
}

void game_action_broadcast(game_t *game, game_player_t *self, char *arg)
{
    game_player_t *player;
    int direction;

    if (!arg || !*arg) {
        csocket_writestr(self->client, "ko\n");
        return;
    }
    for (list_node_t *node = game->players->first; node; node = node->next) {
        player = node->value;
        if (player == self)
            continue;
        direction = calculate_direction(game, self->pos, player->pos);
        direction = get_final_direction(direction, player->dir);
        csocket_printf(player->client, "message %d, %s\n", direction, arg);
    }
    csocket_printf(self->client, "ok\n");
    SERVER_BCW("pbc %s%d %s\n", GAME_SHITTYGUI(game), self->id, arg);
    SERVER_LOG(info, "Player #%d broadcasted: %s", self->id, arg);
}
