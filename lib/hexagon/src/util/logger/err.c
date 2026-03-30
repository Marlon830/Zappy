/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_errv(logger_t *self, const char *format, va_list args)
{
    logger_logv(self, &LL_ERR, format, args);
}

void logger_err(logger_t *self, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    logger_errv(self, format, args);
    va_end(args);
}
