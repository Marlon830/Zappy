/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

#include <signal.h>

void process_sendsignal(process_t process, uint8_t signal)
{
    kill(process, signal);
}
