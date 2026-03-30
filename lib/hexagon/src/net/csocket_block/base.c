/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_block.h"

#include "hexagon/util/mem.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

csocket_block_t *csocket_block_import(uint8_t *buff, size_t size)
{
    csocket_block_t *block = mem_alloc(sizeof(*block));

    *block = (csocket_block_t) {
        .size = size,
        .buff = buff
    };
    return block;
}

csocket_block_t *csocket_block_new(const uint8_t *buff, size_t size)
{
    uint8_t *dup_buff = size ? mem_alloc(sizeof(*buff) * size) : NULL;

    if (dup_buff && buff)
        memcpy(dup_buff, buff, size);
    return csocket_block_import(dup_buff, size);
}

void csocket_block_delete(csocket_block_t *self)
{
    mem_free(self->buff);
    mem_free(self);
}
