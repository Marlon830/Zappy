/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "server_handler.h"

#include "hexagon/util/c.h"
#include "hexagon/util/time.h"

void server_handler_on_preprocess(server_t *server,
    UNUSED ssocket_t *server_socket)
{
    server->pre_time = time_now();
    SERVER_LOG(trace, "Preprocessing handler called");
}
