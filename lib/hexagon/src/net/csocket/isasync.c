/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include <stdbool.h>

bool csocket_isasync(csocket_t *self)
{
    return self->async;
}
