/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

#include <unistd.h>

process_t process_current(void)
{
    return getpid();
}
