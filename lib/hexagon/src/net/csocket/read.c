/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include "hexagon/util/math.h"

#include <assert.h>
#include <string.h>

#include <stdbool.h>

size_t csocket_read(csocket_t *self, void *_buff, size_t size)
{
    uint8_t *buff = _buff;
    size_t move_size;
    size_t read = 0;
    bool block_read = true;

    while (read < size && block_read) {
        block_read = false;
        if (csocket_getin(self) == 0) {
            assert(csocket_sync(self));
            block_read = csocket_getin(self) == CSOCKET_BUFFSIZE;
        }
        move_size = MIN(csocket_getin(self), size - read);
        memcpy(buff, self->in_buff_ptr, move_size);
        self->in_buff_ptr += move_size;
        read += move_size;
        buff += move_size;
    }
    return read;
}
