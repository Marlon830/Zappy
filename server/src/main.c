/*
** EPITECH PROJECT, 2024
** ZOAT
** File description:
** main file
*/

#include "argument.h"
#include "server.h"

static void setup_args_1(list_t *args)
{
    list_append(args, argument_new((argument_t)
        {"-h", "--help", "Display this help message", 0, command_help}));
    list_append(args, argument_new((argument_t)
        {"-l", "--logger-level", "Set the logger level threshold", 1,
        command_logger_level}));
    list_append(args, argument_new((argument_t)
        {"-p", "--port", "Set the port", 1, command_port}));
    list_append(args, argument_new((argument_t)
        {"-x", "--width", "Set the width of the world", 1, command_width}));
    list_append(args, argument_new((argument_t)
        {"-y", "--height", "Set the height of the world", 1, command_height}));
    list_append(args, argument_new((argument_t){"-n", "--teams",
        "Set the name of the teams", -1, command_teams}));
    list_append(args, argument_new((argument_t){"-c", "--client-count",
        "Set the number of clients per team", 1, command_clients_nb}));
    list_append(args, argument_new((argument_t){"-f", "--tick-frequency",
        "Set the game logic frequency (in Hertz)", 1, command_freq}));
    list_append(args, argument_new((argument_t){"-G", "--sync-mode",
        "Set the way the game state is transmitted to ('async', 'explicit')",
        1, command_sync_mode}));
}

static void setup_args_2(list_t *args)
{
    list_append(args, argument_new((argument_t){"-s", "--shitty-gui",
        "Don't add '#' to player IDs so that the reference binary doesn't "
        "crash", 0, command_shitty_gui}));
}

int main(int ac, const char **av)
{
    server_t *server = server_get();

    setup_args_1(server->args);
    setup_args_2(server->args);
    arguments_parse(server->args, ac, av);
    server_run(server);
    server_delete(server);
    return 0;
}
