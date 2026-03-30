/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include "hexagon/util/mem.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

const char *fs_combinepath(const char *path_a, const char *path_b)
{
    static char resolved_path[PATH_MAX];

    snprintf(resolved_path, PATH_MAX, "%s/%s", path_a, path_b);
    return resolved_path;
}
