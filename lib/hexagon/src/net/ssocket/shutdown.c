/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/ssocket.h"

void ssocket_shutdown(ssocket_t *self)
{
    self->listening = false;
}
