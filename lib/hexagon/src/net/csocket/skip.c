/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include "hexagon/util/math.h"

void csocket_skip(csocket_t *self, size_t count)
{
    size_t to_skip;
    size_t skipped = 0;

    while (skipped < count) {
        if (csocket_getin(self) == 0)
            csocket_sync(self);
        to_skip = MIN(count - skipped, csocket_getin(self));
        skipped += to_skip;
        self->in_buff_ptr += to_skip;
    }
}
