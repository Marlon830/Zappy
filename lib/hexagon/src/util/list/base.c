/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/list.h"

#include "hexagon/util/mem.h"

list_t *list_new(void)
{
    list_t *self = STRUCT_NEW(list);

    *self = (list_t) {
        .first = NULL,
        .last = NULL,
        .size = 0ul
    };
    return self;
}

void list_delete(list_t *self)
{
    list_clear(self);
    mem_free(self);
}
