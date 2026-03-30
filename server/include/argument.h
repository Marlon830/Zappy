/*
** EPITECH PROJECT, 2024
** argument
** File description:
** file for argument functions
*/

#pragma once

#include "hexagon/util/list.h"

typedef struct argument_s {
    char *sflag;
    char *lflag;
    char *description;
    int args;
    void (*callback)(const char **args);
} argument_t;

void arguments_parse(list_t *args, int argc, const char **argv);

argument_t *argument_new(argument_t argument);
void argument_delete(argument_t *self);

argument_t *arguments_find(list_t *args, const char *flag);
int arguments_count_variadic(const char **args);

void command_help(const char **args);
void command_logger_level(const char **args);
void command_port(const char **args);
void command_width(const char **args);
void command_height(const char **args);
void command_teams(const char **args);
void command_clients_nb(const char **args);
void command_freq(const char **args);
void command_sync_mode(const char **args);
void command_shitty_gui(const char **args);
