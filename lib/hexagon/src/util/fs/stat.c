/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <assert.h>

struct stat fs_stat(const char *path)
{
    struct stat st;

    if (stat(path, &st) != 0)
        st = (struct stat) {0};
    return st;
}
