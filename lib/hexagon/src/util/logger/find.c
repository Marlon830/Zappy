/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "hexagon/util/logger.h"

#include <stddef.h>
#include <string.h>

const logger_level_t *logger_findlevel(const char *level_name)
{
    static const struct {
        const char *name;
        const logger_level_t *level;
    } levels[] = {
        {"trace", &LL_TRACE},
        {"debug", &LL_DEBUG},
        {"info", &LL_INFO},
        {"warn", &LL_WARN},
        {"err", &LL_ERR},
        {"fatal", &LL_FATAL},
        {NULL, NULL}
    };

    for (int i = 0; levels[i].name; i++)
        if (strcmp(levels[i].name, level_name) == 0)
            return levels[i].level;
    return NULL;
}
