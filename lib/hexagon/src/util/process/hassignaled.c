/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

bool process_hassignaled(process_t process)
{
    process_status_t process_status;

    process_status = process_check(process);
    return process_status.signaled;
}
