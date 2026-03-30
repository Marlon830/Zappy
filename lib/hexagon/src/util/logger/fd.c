/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

void logger_addfd(logger_t *self, int fd)
{
    LIST_APPEND(self->fd_list, fd);
}

void logger_removefd(logger_t *self, int fd)
{
    list_remove(self->fd_list, LIST_FIND(self->fd_list, fd));
}
