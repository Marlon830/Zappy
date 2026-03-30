/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/fmt.h"

#include <stdio.h>

size_t fmt_lengthv(const char *format, va_list args)
{
    va_list args_copy;
    size_t length;

    va_copy(args_copy, args);
    length = vsnprintf(NULL, 0, format, args_copy);
    return length;
}

size_t fmt_length(const char *format, ...)
{
    va_list args;
    size_t length;

    va_start(args, format);
    length = fmt_lengthv(format, args);
    va_end(args);
    return length;
}
