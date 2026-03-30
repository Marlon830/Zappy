/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_linereader.h"

#include "hexagon/util/math.h"
#include "hexagon/util/mem.h"

#include <string.h>

static void csocket_linereader_read_resv(csocket_linereader_t *self,
    size_t wanted)
{
    size_t buff_left = self->buff_ceil - self->buff_ptr;
    size_t buff_ceil_size;

    if (self->buff_ptr > self->buff) {
        memmove(self->buff, self->buff_ptr, buff_left);
        self->buff_ptr = self->buff;
        self->buff_ceil = self->buff_ptr + buff_left;
    }
    if (self->buff_size - buff_left < wanted) {
        buff_ceil_size = self->buff_ceil - self->buff;
        self->buff_size = 1 << (mem_firstlastbit(
            self->buff_size + wanted) + 1);
        MEM_REALLOC(&self->buff, self->buff_size);
        self->buff_ptr = self->buff;
        self->buff_ceil = self->buff_ptr + buff_ceil_size;
    }
}

static char *csocket_linereader_read_prepare(csocket_linereader_t *self)
{
    bool sync_required =
        self->buff_ptr >= self->buff_ceil &&
        csocket_getin(self->socket) == 0;

    if (sync_required) {
        if (csocket_isasync(self->socket))
            return NULL;
        csocket_sync(self->socket);
    }
    if (csocket_getin(self->socket) > 0) {
        csocket_linereader_read_resv(self, csocket_getin(self->socket));
        self->buff_ceil += csocket_read(self->socket,
            self->buff_ceil, csocket_getin(self->socket));
    }
    return self->buff_ptr;
}

const char *csocket_linereader_read(csocket_linereader_t *self,
    const char *delim)
{
    char *prev_buff_ptr = csocket_linereader_read_prepare(self);
    char *delim_ptr;

    if (!prev_buff_ptr)
        return NULL;
    delim_ptr = mem_find(self->buff_ptr, self->buff_ceil - self->buff_ptr,
        delim, strlen(delim));
    if (delim_ptr) {
        *delim_ptr = '\0';
        self->buff_ptr = delim_ptr + strlen(delim);
        return prev_buff_ptr;
    } else
        return NULL;
}
