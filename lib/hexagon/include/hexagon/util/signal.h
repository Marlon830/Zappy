/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <signal.h>

void signal_hook(uint16_t signum);
void signal_unhook(uint16_t signum);
bool signal_hastripped(uint16_t signum);
