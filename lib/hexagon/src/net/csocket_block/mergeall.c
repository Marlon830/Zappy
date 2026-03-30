/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket_block.h"

#include "hexagon/util/mem.h"

#include <string.h>

static void csocket_block_mergeall_calcsize(size_t *master_block_size,
    csocket_block_t *block)
{
    *master_block_size += block->size;
}

static void csocket_block_mergeall_copy(uint8_t **master_block_ptr,
    csocket_block_t *block)
{
    memcpy(*master_block_ptr, block->buff, block->size);
    (*master_block_ptr) += block->size;
    csocket_block_delete(block);
}

csocket_block_t *csocket_block_mergeall(list_t *blocks)
{
    csocket_block_t *master_block;
    uint8_t *master_block_ptr;

    if (list_len(blocks) == 0)
        return NULL;
    master_block = csocket_block_new(NULL, 0);
    LIST_FOREACHC(blocks, &master_block->size,
        &csocket_block_mergeall_calcsize);
    master_block->buff =
        mem_alloc(sizeof(*master_block->buff) * master_block->size);
    master_block_ptr = master_block->buff;
    LIST_FOREACHC(blocks, &master_block_ptr, &csocket_block_mergeall_copy);
    list_clear(blocks);
    return master_block;
}
