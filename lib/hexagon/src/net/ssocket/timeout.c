/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/ssocket.h"

#include <string.h>

const struct timeval *ssocket_gettimeout(ssocket_t *self)
{
    return &self->select_timeout;
}

void ssocket_settimeout(ssocket_t *self, struct timeval *timeout)
{
    memcpy(&self->select_timeout, timeout, sizeof(struct timeval));
}
