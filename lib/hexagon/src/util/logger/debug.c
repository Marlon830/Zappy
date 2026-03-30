/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_debugv(logger_t *self, const char *format, va_list args)
{
    logger_logv(self, &LL_DEBUG, format, args);
}

void logger_debug(logger_t *self, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    logger_debugv(self, format, args);
    va_end(args);
}
