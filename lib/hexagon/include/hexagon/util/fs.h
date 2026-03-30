/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <sys/stat.h>

#include <stdbool.h>

struct stat fs_stat(const char *path);
bool fs_exists(const char *path);
bool fs_isdir(const char *path);
bool fs_isfile(const char *path);

const char *fs_realpath(const char *path);
const char *fs_combinepath(const char *path_a, const char *path_b);
const char *fs_parentpath(const char *path);

bool fs_makedir(const char *path, mode_t mode);

bool fs_deletefile(const char *path);
