/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fs.h"

#include <errno.h>

#include <sys/stat.h>

bool fs_makedir(const char *path, mode_t mode)
{
    int mkdir_status = mkdir(path, mode);

    return mkdir_status == 0
        || (errno == EEXIST && fs_isdir(path));
}
