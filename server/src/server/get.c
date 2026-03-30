/*
** EPITECH PROJECT, 2024
** get
** File description:
** file for get functions
*/

#include "server.h"

server_t *server_get(void)
{
    static server_t *server = NULL;

    if (!server)
        server = server_new();
    return server;
}
