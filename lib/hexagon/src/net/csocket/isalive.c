/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include <sys/ioctl.h>

bool csocket_isalive(csocket_t *csocket)
{
    int bytes_avail;

    return ioctl(csocket->fd, FIONREAD, &bytes_avail) == 0 &&
        bytes_avail > 0;
}
