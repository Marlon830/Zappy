/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_infov(logger_t *self, const char *format, va_list args)
{
    logger_logv(self, &LL_INFO, format, args);
}

void logger_info(logger_t *self, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    logger_infov(self, format, args);
    va_end(args);
}
