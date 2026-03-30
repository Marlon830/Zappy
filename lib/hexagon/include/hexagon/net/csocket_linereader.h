/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include "hexagon/net/csocket.h"

#include <stddef.h>

typedef struct csocket_linereader_s {
    csocket_t *socket;

    char *buff;
    char *buff_ptr;
    char *buff_ceil;
    size_t buff_size;
} csocket_linereader_t;

csocket_linereader_t *csocket_linereader_new(csocket_t *socket);
void csocket_linereader_delete(csocket_linereader_t *self);

const char *csocket_linereader_read(csocket_linereader_t *self,
    const char *delim);
void csocket_linereader_clear(csocket_linereader_t *self);

size_t csocket_linereader_getbuffsize(csocket_linereader_t *self);
