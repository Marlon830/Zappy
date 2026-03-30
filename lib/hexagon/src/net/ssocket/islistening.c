/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/ssocket.h"

bool ssocket_islistening(ssocket_t *self)
{
    return self->listening;
}
