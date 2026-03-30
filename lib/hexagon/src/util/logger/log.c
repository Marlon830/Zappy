/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

#include <stdarg.h>

void logger_log(logger_t *self, const logger_level_t *level,
    const char *format, ...)
{
    va_list va_args;

    va_start(va_args, format);
    logger_logv(self, level, format, va_args);
    va_end(va_args);
}
