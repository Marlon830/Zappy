/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include "hexagon/util/c.h"

#include <stdbool.h>
#include <stddef.h>

#define MAP_INITSIZE 8
#define MAP_RESIZETHRESHOLD 0.7

typedef struct map_entry_s {
    void *key;
    void *value;
} map_entry_t;

typedef struct map_s {
    size_t key_size;

    size_t size;
    size_t count;
    map_entry_t *values;
} map_t;

map_t *map_new(size_t key_size);
#define MAP_NEW(KT) map_new(sizeof(KT))
void map_delete(map_t *self);

size_t map_hash(map_t *self, void *key);

size_t map_len(map_t *self);
void map_resize(map_t *self, size_t new_size);
void map_clear(map_t *self);

bool map_has(map_t *self, void *key);
#define MAP_HAS(S, K) map_has(S, (void *) K)
void map_put(map_t *self, void *key, void *value);
#define MAP_PUT(S, K, V) map_put(S, (void *) K, V)
void *map_get(map_t *self, void *key);
#define MAP_GET(S, K) map_get(S, (void *) K)
void map_remove(map_t *self, void *key);
#define MAP_REMOVE(S, K) map_remove(S, (void *) K)

typedef void (map_foreach_lamb_t)(void *key, void *value);

void map_foreach(map_t *self, map_foreach_lamb_t *callback);
#define MAP_FOREACH(S, C) map_foreach(S, FUNC C)

typedef void (map_foreachc_lamb_t)(void *context, void *key, void *value);

void map_foreachc(map_t *self, void *context, map_foreachc_lamb_t *callback);
#define MAP_FOREACHC(S, C, F) map_foreachc(S, C, FUNC F)
