/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include "hexagon/util/mem.h"

#include <limits.h>
#include <string.h>

const char *fs_parentpath(const char *path)
{
    static char resolved_path[PATH_MAX];
    size_t path_len = strlen(path);
    char *path_ptr = resolved_path + path_len - 1;

    strncpy(resolved_path, path, ARRAY_SIZE(resolved_path));
    if (*path_ptr == '/')
        --path_ptr;
    while (path_ptr > resolved_path && *path_ptr != '/')
        --path_ptr;
    if (path_ptr == resolved_path)
        return "/";
    *path_ptr = '\0';
    return resolved_path;
}
