/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#pragma once

#include "watcher.h"
#include "player.h"

#include "hexagon/net/csocket.h"
#include "hexagon/net/csocket_linereader.h"

#include <stdbool.h>

typedef enum client_type_e {
    CLIENTTYPE_UNKNOWN,
    CLIENTTYPE_WATCHER,
    CLIENTTYPE_PLAYER
} client_type_t;

typedef struct client_s {
    csocket_t *socket;
    csocket_linereader_t *reader;

    client_type_t type;
    union {
        game_watcher_t *watcher;
        game_player_t *player;
    };
} client_t;

client_t *client_new(csocket_t *socket);
void client_delete(client_t *client);

void client_as_watcher(client_t *self);
bool client_as_player(client_t *self, const char *team_name,
    csocket_t *client_socket);

game_watcher_t *client_watcher(client_t *self);
game_player_t *client_player(client_t *self);
