/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <stddef.h>
#include <stdint.h>

void *mem_alloc(size_t size);
void mem_realloc(void **ptr, size_t size);
#define MEM_REALLOC(PTR, SIZE) mem_realloc((void **) (PTR), SIZE)
void mem_free(void *ptr);
#define MEM_FREE(PTR) mem_free((void *) PTR)

void *mem_find(void *haystack, size_t haystack_size,
    const void *needle, size_t needle_size);

uint8_t mem_firstlastbit(size_t n);

#define STRUCT_NEW(TYPE) (TYPE##_t *) mem_alloc(sizeof(TYPE##_t))
#define STRUCT_NEWIN(TYPE, NAME) TYPE##_t *NAME = STRUCT_NEW(TYPE)

#define ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(*ARR))
