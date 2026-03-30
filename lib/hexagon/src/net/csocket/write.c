/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"
#include "hexagon/net/csocket_block.h"

#include "hexagon/util/math.h"

#include <assert.h>
#include <string.h>

static size_t csocket_write_makeblock(csocket_t *self,
    uint8_t *buff, size_t size, size_t written)
{
    if (size == written)
        return size;
    list_append(self->out_block_queue,
        csocket_block_new(buff + written, size - written));
    return size;
}

size_t csocket_write(csocket_t *self, const void *_buff, size_t size)
{
    uint8_t *buff = (uint8_t *) _buff;
    size_t to_write;
    size_t writc = 0;
    bool block_write = true;
    bool flush_ok = true;

    while (writc < size && block_write) {
        block_write = false;
        to_write = MIN(CSOCKET_BUFFSIZE - csocket_getout(self), size - writc);
        memcpy(self->out_buff_ptr, buff + writc, to_write);
        self->out_buff_ptr += to_write;
        writc += flush_ok * to_write;
        if (csocket_getout(self) == CSOCKET_BUFFSIZE) {
            flush_ok = csocket_flush(self);
            block_write = flush_ok && csocket_getout(self) == 0;
        }
    }
    if (!csocket_isasync(self) || flush_ok)
        return writc;
    return csocket_write_makeblock(self, buff, size, writc);
}

size_t csocket_writestr(csocket_t *self, const char *str)
{
    size_t written = csocket_write(self, str, strlen(str));

    return written;
}
