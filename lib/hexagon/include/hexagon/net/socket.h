/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <stdint.h>

#include <arpa/inet.h>

typedef void (socket_contextdeleter_t)(void *context);

typedef struct socket_s {
    int fd;

    char ip_addr[INET_ADDRSTRLEN + 1];
    uint16_t port;

    void *context;
    socket_contextdeleter_t *context_deleter;
} socket_t;

#define SOCKET_GETIPADDR(SELF) socket_getipaddr((socket_t *) SELF)
const char *socket_getipaddr(socket_t *self);
#define SOCKET_GETPORT(SELF) socket_getport((socket_t *) SELF)
uint16_t socket_getport(socket_t *self);
#define SOCKET_GETSTRADDR(SELF) socket_getstraddr((socket_t *) SELF)
const char *socket_getstraddr(socket_t *self);
#define SOCKET_GETWORDADDR(SELF, A) socket_getwordaddr((socket_t *) SELF, A)
void socket_getwordaddr(socket_t *self, uint8_t addr[4]);

#define SOCKET_BINDCONTEXT(S, C, D) socket_bindcontext((socket_t *) S, C, D)
void socket_bindcontext(socket_t *self, void *context,
    socket_contextdeleter_t *context_deleter);
#define SOCKET_GETCONTEXT(SELF, T) socket_getcontext((socket_t *) SELF)
void *socket_getcontext(socket_t *self);

#define SOCKET_FULLADDRSTRLEN (INET_ADDRSTRLEN + 1 + 5)
