/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <unistd.h>

bool fs_deletefile(const char *path)
{
    return unlink(path) == 0;
}
