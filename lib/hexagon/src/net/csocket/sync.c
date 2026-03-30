/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include "hexagon/util/mem.h"

#include <unistd.h>

#include <string.h>

bool csocket_sync(csocket_t *self)
{
    size_t copy_size = self->in_buff_ceil - self->in_buff_ptr;
    size_t read_size = ARRAY_SIZE(self->in_buff);
    ssize_t actually_read;
    uint8_t *buff_ptr = self->in_buff;

    if (copy_size > 0) {
        memmove(self->in_buff, self->in_buff_ptr, copy_size);
        buff_ptr += copy_size;
        read_size -= copy_size;
    }
    actually_read = recv(self->fd, buff_ptr, read_size - copy_size, 0);
    self->in_buff_ptr = self->in_buff;
    self->in_buff_ceil = self->in_buff + copy_size + actually_read;
    return actually_read >= 0;
}
