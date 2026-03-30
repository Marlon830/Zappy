/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include "hexagon/net/socket.h"

#include "hexagon/util/list.h"

#include <sys/socket.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SSOCKET_BACKLOG 16

typedef struct csocket_s csocket_t;

typedef struct ssocket_s {
    int fd;

    char ip_addr[INET_ADDRSTRLEN + 1];
    uint16_t port;

    void *context;
    socket_contextdeleter_t *context_deleter;

    /* --- class-specific fields --- */
    bool listening;
    struct timeval select_timeout;

    list_t *clients;
    fd_set read_client_fds;
    fd_set write_client_fds;
} ssocket_t;

typedef void (ssocket_serverhandler_t)(
    void *context, ssocket_t *server_socket);
typedef void (ssocket_clienthandler_t)(
    void *context, ssocket_t *server_socket, csocket_t *client_socket);

typedef struct ssocket_handlers_s {
    ssocket_serverhandler_t *on_preprocess;
    ssocket_serverhandler_t *on_postprocess;
    ssocket_serverhandler_t *on_signal;

    ssocket_clienthandler_t *on_connect;
    ssocket_clienthandler_t *on_disconnect;
    ssocket_clienthandler_t *when_readable;
    ssocket_clienthandler_t *when_writable;
} ssocket_handlers_t;

ssocket_t *ssocket_new(const char *ip, uint16_t port);
void ssocket_delete(ssocket_t *self);

/* --- class methods --- */

void ssocket_settimeout(ssocket_t *self, struct timeval *timeout);
const struct timeval *ssocket_gettimeout(ssocket_t *self);

bool ssocket_islistening(ssocket_t *self);
void ssocket_listen(ssocket_t *self, ssocket_handlers_t *handlers);

void ssocket_shutdown(ssocket_t *self);

void ssocket_close(ssocket_t *self, csocket_t *client_socket);

#define SSOCKET_FOREACH(S, c) LIST_FOREACH(S->clients, c)
#define SSOCKET_FOREACHC(S, c, C) LIST_FOREACHC(S->clients, c, C)
