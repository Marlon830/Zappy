/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/time.h"

#include "hexagon/util/mem.h"

#include <sys/time.h>

const char *time_tostring(const char *format, const time_t *time)
{
    static char time_buffer[TIME_BUFFSIZE];

    strftime(time_buffer, ARRAY_SIZE(time_buffer), format, localtime(time));
    return time_buffer;
}

const char *time_formatnow(const char *format)
{
    time_t now = time(NULL);

    return time_tostring(format, &now);
}

long time_now(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    return time_now.tv_sec * (long) 1e6 + time_now.tv_usec;
}
