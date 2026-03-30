/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server.h"
#include "server_handler.h"

#include "hexagon/net/socket.h"

#include "hexagon/util/c.h"

#include <signal.h>
#include <stdio.h>

static ssocket_handlers_t server_handler_table = {
    .on_preprocess = FUNC &server_handler_on_preprocess,
    .on_postprocess = FUNC &server_handler_on_postprocess,
    .on_connect = FUNC &server_handler_on_connect,
    .on_disconnect = FUNC &server_handler_on_disconnect,
    .when_readable = FUNC &server_handler_when_readable,
    .when_writable = FUNC &server_handler_when_writable
};

static struct timeval * server_run_getfreqtime(int frequency)
{
    static struct timeval freqtime = {0};

    freqtime.tv_usec = 1e6 / frequency;
    return &freqtime;
}

void server_setfreq(server_t *self, int freq)
{
    struct timeval *freqtime = server_run_getfreqtime(freq);

    self->freq = freq;
    ssocket_settimeout(self->socket, freqtime);
}

static void server_on_signal(int signum)
{
    server_t *server = server_get();

    if (signum == SIGINT)
        puts("");
    SERVER_LOG(info, "Received signal %d, stopping server", signum);
    ssocket_shutdown(server->socket);
}

void server_run(server_t *self)
{
    if (list_len(self->game->teams) == 0) {
        LOGGER_LOG(self->logger, fatal, "No teams were specified");
        return;
    }
    self->socket = ssocket_new("0.0.0.0", self->port);
    if (!self->socket) {
        LOGGER_LOG(self->logger, fatal,
            "Failed to create server socket on port %d", self->port);
        return;
    }
    SOCKET_BINDCONTEXT(self->socket, self, NULL);
    game_init(self->game, self->ppt);
    signal(SIGINT, &server_on_signal);
    LOGGER_LOG(self->logger, info, "Server is running on port %d", self->port);
    server_setfreq(self, self->freq);
    ssocket_listen(self->socket, &server_handler_table);
    LOGGER_LOG(self->logger, info, "Server stopped, goodbye :]");
}
