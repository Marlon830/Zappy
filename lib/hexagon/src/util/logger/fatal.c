/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_fatalv(logger_t *self, const char *format, va_list args)
{
    logger_logv(self, &LL_FATAL, format, args);
}

void logger_fatal(logger_t *self, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    logger_fatalv(self, format, args);
    va_end(args);
}
