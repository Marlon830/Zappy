/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"
#include "hexagon/net/csocket_block.h"

#include "hexagon/util/math.h"

#include <sys/types.h>

#include <string.h>
#include <unistd.h>

static void csocket_flush_processblocks(csocket_t *self)
{
    csocket_block_t *merged_block;
    size_t out_avail = CSOCKET_BUFFSIZE - csocket_getout(self);

    if (list_len(self->out_block_queue) == 0 ||
        out_avail == 0)
        return;
    merged_block = csocket_block_mergeall(self->out_block_queue);
    out_avail = MIN(out_avail, merged_block->size);
    memmove(self->out_buff_ptr, merged_block->buff, out_avail);
    self->out_buff_ptr += out_avail;
    if (csocket_block_truncate(merged_block, out_avail))
        list_append(self->out_block_queue, merged_block);
}

bool csocket_flush(csocket_t *self)
{
    ssize_t written;

    while (csocket_getout(self) > 0) {
        if (csocket_isasync(self))
            csocket_flush_processblocks(self);
        written = send(self->fd, self->out_buff, csocket_getout(self),
            MSG_NOSIGNAL);
        if (written < 0)
            return false;
        memmove(self->out_buff, self->out_buff + written,
            csocket_getout(self) - written);
        self->out_buff_ptr -= written;
    }
    return true;
}
