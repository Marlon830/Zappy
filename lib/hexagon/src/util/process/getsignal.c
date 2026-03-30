/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

#include <assert.h>

uint16_t process_getsignal(process_t process)
{
    process_status_t process_status;

    process_status = process_check(process);
    assert(process_status.signaled);
    return process_status.signal;
}
