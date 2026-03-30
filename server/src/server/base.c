/*
** EPITECH PROJECT, 2024
** base
** File description:
** file for base functions
*/

#include "server.h"

#include "hexagon/util/mem.h"
#include "hexagon/util/c.h"
#include "hexagon/util/logger.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

server_t *server_new(void)
{
    STRUCT_NEWIN(server, self);
    self->ppt = 2;
    self->freq = 100;
    self->port = 7894;
    self->args = list_new();
    self->game = game_new();
    self->logger = logger_new(&LL_INFO);
    self->un_time = 0;
    self->socket = NULL;
    logger_addfd(self->logger, STDOUT_FILENO);
    srand(time(NULL));
    return self;
}

void server_delete(server_t *self)
{
    list_foreach(self->args, FUNC &argument_delete);
    list_delete(self->args);
    game_delete(self->game);
    if (self->socket)
        ssocket_delete(self->socket);
    logger_delete(self->logger);
    mem_free(self);
}
