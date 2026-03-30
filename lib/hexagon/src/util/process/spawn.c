/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

#include <unistd.h>
#include <stdlib.h>

process_t process_spawn(process_callback_t *callback, void *context)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0)
        exit(callback(context));
    return child_pid;
}
