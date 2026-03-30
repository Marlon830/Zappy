/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_block.h"

#include "hexagon/util/mem.h"
#include "hexagon/util/math.h"

#include <string.h>

bool csocket_block_truncate(csocket_block_t *self, size_t count)
{
    count = MAX(count, self->size);
    if (count == 0 || count == self->size) {
        csocket_block_delete(self);
        return false;
    }
    memmove(self->buff, self->buff + count, self->size - count);
    self->size -= count;
    MEM_REALLOC(self->buff, self->size);
    return true;
}
