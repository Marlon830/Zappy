/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <sys/stat.h>
#include <stddef.h>

bool fs_exists(const char *path)
{
    struct stat sb;

    return stat(path, &sb) == 0;
}
