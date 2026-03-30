/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <sys/stat.h>

bool fs_isfile(const char *path)
{
    struct stat sb = fs_stat(path);

    return S_ISREG(sb.st_mode);
}
