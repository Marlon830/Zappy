/*
** EPITECH PROJECT, 2024
** teams
** File description:
** file for teams functions
*/

#include "argument.h"
#include "server.h"
#include "team.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static bool command_teams_contains(list_t *teams, const char *name)
{
    game_team_t *team;

    for (list_node_t *node = teams->first; node; node = node->next) {
        team = node->value;
        if (strcmp(team->name, name) == 0)
            return true;
    }
    return false;
}

void command_teams(const char **args)
{
    server_t *server = server_get();

    for (int i = 0; args[i] && args[i][0] != '-'; i++) {
        if (strcmp(args[i], "GRAPHIC") == 0) {
            fprintf(stderr, "You can't use 'GRAPHIC' as a team!\n");
            exit(84);
        } else if (command_teams_contains(server->game->teams, args[i])) {
            fprintf(stderr, "Team %s already exists!\n", args[i]);
            exit(84);
        }
        list_append(server->game->teams, team_new(args[i]));
        SERVER_LOG(info, "Created team %s", args[i]);
    }
}
