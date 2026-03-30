/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "hexagon/util/list.h"

#pragma once

typedef struct csocket_block_s {
    size_t size;
    uint8_t *buff;
} csocket_block_t;

csocket_block_t *csocket_block_import(uint8_t *buff, size_t size);
csocket_block_t *csocket_block_new(const uint8_t *buff, size_t size);
void csocket_block_delete(csocket_block_t *self);

csocket_block_t *csocket_block_mergeall(list_t *blocks);

size_t csocket_block_getsize(csocket_block_t *self);
uint8_t *csocket_block_getbuff(csocket_block_t *self);
bool csocket_block_truncate(csocket_block_t *self, size_t count);
