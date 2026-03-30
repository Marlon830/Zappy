/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_tracev(logger_t *self, const char *format, va_list args)
{
    logger_logv(self, &LL_TRACE, format, args);
}

void logger_trace(logger_t *self, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    logger_tracev(self, format, args);
    va_end(args);
}
