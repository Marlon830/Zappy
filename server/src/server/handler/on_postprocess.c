/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server_handler.h"

#include "hexagon/util/c.h"
#include "hexagon/util/time.h"

static void server_handler_on_postprocess_client(csocket_t *client_socket)
{
    SERVER_LOG(trace, "Checking if client %s needs to be flushed",
        SOCKET_GETSTRADDR(client_socket));
    if (csocket_getout(client_socket) == 0)
        return;
    SERVER_LOG(trace, "Flushing %zu bytes to client %s",
        csocket_getout(client_socket), SOCKET_GETSTRADDR(client_socket));
    csocket_flush(client_socket);
}

void server_handler_on_postprocess(server_t *server,
    UNUSED ssocket_t *server_socket)
{
    long post_time = time_now();
    long post_time_us;
    long tick_count;

    SERVER_LOG(trace, "Postprocessing handler called");
    post_time_us = post_time - server->pre_time;
    SERVER_LOG(debug, "Server loop took %.02f ms (+%.02f ms backed) to "
        "catch up", (float) post_time_us / 1e3, (float) server->un_time / 1e3);
    post_time_us += server->un_time;
    tick_count = post_time_us / (1e6 / server->freq);
    server->un_time = post_time_us % ((long) 1e6 / server->freq);
    for (int i = 0; i < tick_count; i++)
        game_tick(server->game);
    SERVER_LOG(trace, "Server ticked %u time(s)", tick_count);
    SSOCKET_FOREACH(server->socket, &server_handler_on_postprocess_client);
}
