/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_warnv(logger_t *self, const char *format, va_list args)
{
    logger_logv(self, &LL_WARN, format, args);
}

void logger_warn(logger_t *self, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    logger_warnv(self, format, args);
    va_end(args);
}
