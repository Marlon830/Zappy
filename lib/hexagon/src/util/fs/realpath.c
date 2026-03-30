/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

const char *fs_realpath(const char *path)
{
    static char resolved_path[PATH_MAX];

    if (!realpath(path, resolved_path))
        return NULL;
    return resolved_path;
}
