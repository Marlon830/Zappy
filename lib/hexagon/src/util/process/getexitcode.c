/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

#include <assert.h>

uint8_t process_getexitcode(process_t process)
{
    process_status_t process_status;

    process_status = process_check(process);
    assert(process_status.exited);
    return process_status.exit_code;
}
