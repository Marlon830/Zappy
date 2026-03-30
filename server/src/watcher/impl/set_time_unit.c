/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"
#include "watcher_handler.h"

#include "server.h"
#include "game.h"

#include "hexagon/util/c.h"

#include <stdlib.h>

void game_watcher_cmd_set_time_unit(UNUSED game_watcher_t *self,
    csocket_t *client, list_t *args)
{
    server_t *server = server_get();
    char *freq_ptr;
    long freq = strtol(list_at(args, 1), &freq_ptr, 10);

    if (*freq_ptr || freq < 1) {
        SERVER_LOG(trace, "Invalid tick frequency %s given from client %s",
            list_at(args, 1), SOCKET_GETSTRADDR(client));
        csocket_writeln(client, "sbp");
        return;
    }
    server_setfreq(server, freq);
    csocket_printf(client, "sst %ld\n", freq);
    SERVER_LOG(trace, "Tick frequency set to %ld by client %s", freq,
        SOCKET_GETSTRADDR(client));
}
