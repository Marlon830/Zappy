/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <sys/stat.h>

bool fs_isdir(const char *path)
{
    struct stat sb = fs_stat(path);

    return S_ISDIR(sb.st_mode);
}
