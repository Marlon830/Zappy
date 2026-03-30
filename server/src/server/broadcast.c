/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server.h"

void server_broadcastv(server_t *self, client_type_t type,
    const char *fmt, va_list ap)
{
    csocket_t *client_socket;
    client_t *client;

    for (list_node_t *node = self->socket->clients->first; node;
        node = node->next) {
        client_socket = node->value;
        client = SOCKET_GETCONTEXT(client_socket, client);
        if (client->type == type)
            csocket_vprintf(client->socket, fmt, ap);
    }
}

void server_broadcast(server_t *self, client_type_t type,
    const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    server_broadcastv(self, type, fmt, ap);
    va_end(ap);
}

void server_broadcast_callback(server_t *self, client_type_t type,
    void (*callback)(csocket_t *, void *), void *context)
{
    csocket_t *client_socket;
    client_t *client;

    for (list_node_t *node = self->socket->clients->first; node;
        node = node->next) {
        client_socket = node->value;
        client = SOCKET_GETCONTEXT(client_socket, client);
        if (client->type != type)
            continue;
        callback(client_socket, context);
    }
}
