/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_setthreshold(logger_t *self, const logger_level_t *level)
{
    self->level_threshold = level->level;
}

int logger_getthreshold(logger_t *self)
{
    return self->level_threshold;
}
