/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include "hexagon/util/fmt.h"

#include <stdio.h>

size_t csocket_vprintf(csocket_t *self, const char *format, va_list args)
{
    va_list args_copy;
    char buffer[fmt_lengthv(format, args) + 1];

    va_copy(args_copy, args);
    vsnprintf(buffer, sizeof(buffer), format, args_copy);
    return csocket_write(self, buffer, sizeof(buffer) - 1);
}

size_t csocket_printf(csocket_t *self, const char *format, ...)
{
    va_list args;
    size_t ret;

    va_start(args, format);
    ret = csocket_vprintf(self, format, args);
    va_end(args);
    return ret;
}
