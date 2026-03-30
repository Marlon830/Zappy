/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

#include "hexagon/util/mem.h"

#include <limits.h>

logger_t *logger_new(const logger_level_t *level)
{
    STRUCT_NEWIN(logger, logger);
    logger->fd_list = list_new();
    logger_setthreshold(logger, level);
    return logger;
}

void logger_delete(logger_t *self)
{
    list_delete(self->fd_list);
    mem_free(self);
}
