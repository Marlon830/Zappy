/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <time.h>

#define TIME_BUFFSIZE 512

const char *time_tostring(const char *format, const time_t *time);
const char *time_formatnow(const char *format);

long time_now(void);
