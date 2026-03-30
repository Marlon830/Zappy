/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <stdarg.h>
#include <stddef.h>

size_t fmt_lengthv(const char *format, va_list args);
size_t fmt_length(const char *format, ...);
