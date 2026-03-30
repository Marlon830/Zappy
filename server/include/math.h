/*
** EPITECH PROJECT, 2024
** math
** File description:
** file for math functions
*/

#pragma once

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct vec2i_s {
    int x;
    int y;
} vec2i_t;

typedef struct recti_s {
    int x;
    int y;
    int w;
    int h;
} recti_t;
