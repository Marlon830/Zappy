/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#pragma once

#include "argument.h"
#include "game.h"
#include "client.h"

#include "hexagon/net/ssocket.h"

#include "hexagon/util/logger.h"

#include <stdarg.h>
#include <time.h>

typedef struct server_s {
    const logger_level_t *llevel;
    int port;
    int freq;
    int ppt;
    list_t *args;

    game_t *game;
    long pre_time;
    long un_time;

    ssocket_t *socket;
    logger_t *logger;
} server_t;

server_t *server_new(void);
void server_delete(server_t *self);

void server_setfreq(server_t *self, int freq);
void server_run(server_t *self);

void server_broadcastv(server_t *self, client_type_t type,
    const char *fmt, va_list ap);
void server_broadcast(server_t *self, client_type_t type,
    const char *fmt, ...);

void server_broadcast_callback(server_t *self, client_type_t type,
    void (*callback)(csocket_t *, void *), void *context);

server_t *server_get(void);

#define SERVER_LOG(...) LOGGER_LOG(server_get()->logger, __VA_ARGS__)
#define SERVER_BC(T, F, ...) server_broadcast(server_get(), T, F, __VA_ARGS__)
#define SERVER_BCW(F, ...) server_broadcast(server_get(), 1, F, __VA_ARGS__)
#define SERVER_BCWF(f, x) server_broadcast_callback(server_get(), 1, f, x)
