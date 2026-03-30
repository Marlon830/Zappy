/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include "hexagon/net/socket.h"

#include "hexagon/util/list.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define CSOCKET_BUFFSIZE 2048ul

typedef void (csocket_contextdeleter_t)(void *context);

typedef struct csocket_s {
    int fd;

    char ip_addr[INET_ADDRSTRLEN + 1];
    uint16_t port;

    void *context;
    socket_contextdeleter_t *context_deleter;

    /* --- class-specific fields --- */
    bool async;

    uint8_t in_buff[CSOCKET_BUFFSIZE];
    uint8_t *in_buff_ptr;
    uint8_t *in_buff_ceil;

    uint8_t out_buff[CSOCKET_BUFFSIZE];
    uint8_t *out_buff_ptr;
    list_t *out_block_queue;
} csocket_t;

csocket_t *csocket_new(const char *ip, uint16_t port);
csocket_t *csocket_fromfd(int fd, bool async);
void csocket_delete(csocket_t *self);

/* --- class methods --- */

bool csocket_isalive(csocket_t *self);
bool csocket_isasync(csocket_t *self);

size_t csocket_getin(csocket_t *self);
size_t csocket_getout(csocket_t *self);

bool csocket_sync(csocket_t *self);
size_t csocket_read(csocket_t *self, void *buff, size_t size);
void csocket_skip(csocket_t *self, size_t count);

bool csocket_flush(csocket_t *self);

size_t csocket_write(csocket_t *self, const void *buff, size_t size);
size_t csocket_writestr(csocket_t *self, const char *str);
bool csocket_writelnsep(csocket_t *self, const char *str, char sep);
bool csocket_writeln(csocket_t *self, const char *str);

size_t csocket_vprintf(csocket_t *self, const char *format, va_list args);
size_t csocket_printf(csocket_t *self, const char *format, ...);
