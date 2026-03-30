/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct list_node_s {
    void *value;
    struct list_node_s *next;
    struct list_node_s *prev;
} list_node_t;

list_node_t *list_node_new(void *value);
void list_node_delete(list_node_t *self);

typedef struct list_s {
    list_node_t *first;
    list_node_t *last;
    size_t size;
} list_t;

list_t *list_new(void);
void list_delete(list_t *self);

size_t list_len(list_t *self);

list_node_t *list_atn(list_t *self, size_t i);
void *list_at(list_t *self, size_t i);
#define LIST_AT(SELF, I, TYPE) ((TYPE##_t *) list_at(SELF, I))

void list_insert(list_t *self, size_t i, void *value);
#define LIST_INSERT(SELF, I, VAL) list_insert(SELF, I, (void *) (size_t) VAL)
void list_push(list_t *self, void *value);
#define LIST_PUSH(SELF, VAL) list_push(SELF, (void *) (size_t) VAL)
void list_append(list_t *self, void *value);
#define LIST_APPEND(SELF, VAL) list_append(SELF, (void *) (size_t) VAL)

void list_remove_node(list_t *self, list_node_t *node);
void *list_remove(list_t *self, size_t i);
void *list_pop(list_t *self);
void *list_sub(list_t *self);

void list_clear(list_t *self);

typedef void (list_foreach_lamb_t)(void *value);
void list_foreach(list_t *self, list_foreach_lamb_t *callback);

#define LIST_FOREACH(S, C) list_foreach(S, (list_foreach_lamb_t *) C)

typedef void (list_foreachc_lamb_t)(void *context, void *value);
void list_foreachc(list_t *self,
    void *context, list_foreachc_lamb_t *callback);

#define LIST_FOREACHC(S, c, C) list_foreachc(S, c, (list_foreachc_lamb_t *) C)

size_t list_find(list_t *self, void *value);
#define LIST_FIND(SELF, VAL) list_find(SELF, (void *) (intptr_t) VAL)
size_t list_findeq(list_t *self, void *value, size_t member_size);
#define LIST_FINDEQ(S, V, T) list_findeq(S, (void *) (intptr_t) V, sizeof(T))
