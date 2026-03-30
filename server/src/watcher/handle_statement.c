/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#include "watcher.h"

#include "server.h"

#include "hexagon/net/csocket.h"

#include <stdbool.h>
#include <string.h>

static list_t *game_watcher_split_args(char *statement)
{
    list_t *args = list_new();
    char *arg = strtok(statement, " ");

    while (arg) {
        list_append(args, arg);
        arg = strtok(NULL, " ");
    }
    return args;
}

void game_watcher_execute_statement(game_watcher_t *self, csocket_t *client,
    const char *statement, const game_watcher_cmd_t *cmd)
{
    char statement_scratch[strlen(statement) + 1];
    list_t *args;

    strcpy(statement_scratch, statement);
    args = game_watcher_split_args(statement_scratch);
    if (list_len(args) != 1ul + cmd->arg_count) {
        SERVER_LOG(warn, "Invalid argument count for command '%s' requested "
            "by watcher %s",
            cmd->name, SOCKET_GETSTRADDR(client));
        csocket_writeln(client, "sbp");
    } else {
        cmd->handler(self, client, args);
        SERVER_LOG(debug, "Command '%s' requested by watcher %s executed "
            "successfully", cmd->name, SOCKET_GETSTRADDR(client));
    }
    list_delete(args);
}

bool game_watcher_handle_statement(game_watcher_t *self, csocket_t *client,
    const char *statement)
{
    for (const game_watcher_cmd_t *cmd = game_watcher_handlers; cmd->name;
        cmd++) {
        if (strncmp(statement, cmd->name, strlen(cmd->name)) == 0) {
            SERVER_LOG(debug, "Found matching command handler for '%s' "
                "requested by watcher %s",
                cmd->name, SOCKET_GETSTRADDR(client));
            game_watcher_execute_statement(self, client, statement,
                cmd);
            return true;
        }
    }
    SERVER_LOG(debug, "No matching command handler found for '%s' requested "
        "by watcher %s", statement, SOCKET_GETSTRADDR(client));
    return false;
}
