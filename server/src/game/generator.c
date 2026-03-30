/*
** EPITECH PROJECT, 2024
** generator
** File description:
** file for generator functions
*/

#include "server.h"
#include "hexagon/util/mem.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

void game_generate_map(game_t *game)
{
    size_t size = sizeof(game_inventory_t) * game->width * game->height;

    game->map = mem_alloc(size);
    memset(game->map, 0, size);
    game_generate_resources(game);
}

void game_send_map(csocket_t *client_socket)
{
    client_t *client = SOCKET_GETCONTEXT(client_socket, client);

    if (client->type != CLIENTTYPE_WATCHER)
        return;
    game_watcher_handle_statement(client_watcher(client), client->socket,
        "mct");
}

void game_generate_resources(game_t *game)
{
    server_t *server = server_get();

    if (!game->map)
        return;
    game_generate_resource(game, RESOURCE_FOOD, .5);
    game_generate_resource(game, RESOURCE_LINEMATE, .3);
    game_generate_resource(game, RESOURCE_DERAUMERE, .15);
    game_generate_resource(game, RESOURCE_SIBUR, .1);
    game_generate_resource(game, RESOURCE_MENDIANE, .1);
    game_generate_resource(game, RESOURCE_PHIRAS, .08);
    game_generate_resource(game, RESOURCE_THYSTAME, .05);
    if (game->sync_mode != GAME_SYNC_ASYNC)
        return;
    SSOCKET_FOREACH(server->socket, game_send_map);
}

void game_generate_resource(game_t *game, game_resource_t type, double density)
{
    int amount = (int)(game->width * game->height * density) -
        game->resources.items[type];
    int x;
    int y;

    for (int i = 0; i < amount; i++) {
        x = rand() % game->width;
        y = rand() % game->height;
        game->map[y * game->width + x].items[type]++;
    }
    game->resources.items[type] += MAX(amount, 0);
}
