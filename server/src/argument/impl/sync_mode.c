/*
** EPITECH PROJECT, 2024
** argument
** File description:
** file for argument functions
*/

#include "argument.h"

#include "server.h"
#include "game.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void command_sync_mode(const char **args)
{
    server_t *server = server_get();

    if (strcmp(args[0], "async") == 0)
        server->game->sync_mode = GAME_SYNC_ASYNC;
    else if (strcmp(args[0], "explicit") == 0)
        server->game->sync_mode = GAME_SYNC_EXPLICIT;
    else {
        fprintf(stderr, "Invalid sync mode '%s'\n", args[0]);
        exit(84);
    }
}
