/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "argument.h"
#include "server.h"

#include "hexagon/util/c.h"

void command_shitty_gui(UNUSED const char **args)
{
    server_t *server = server_get();

    server->game->shitty_gui = true;
}
