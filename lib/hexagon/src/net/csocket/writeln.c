/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"

#include <string.h>
#include <stdbool.h>

bool csocket_writelnsep(csocket_t *self, const char *str, char sep)
{
    return
        csocket_writestr(self, str) == strlen(str) &&
        csocket_write(self, &sep, 1) == 1;
}

bool csocket_writeln(csocket_t *self, const char *str)
{
    return csocket_writelnsep(self, str, '\n');
}
