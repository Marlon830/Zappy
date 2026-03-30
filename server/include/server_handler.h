/*
** EPITECH PROJECT, 2024
** server
** File description:
** file for server functions
*/

#pragma once

#include "server.h"

#define SERVER_GRAPHIC_TEAMNAME "GRAPHIC"

void server_handler_on_preprocess(server_t *server, ssocket_t *server_socket);
void server_handler_on_postprocess(server_t *server, ssocket_t *server_socket);

void server_handler_on_connect(
    server_t *server, ssocket_t *server_socket, csocket_t *client_socket);
void server_handler_on_disconnect(
    server_t *server, ssocket_t *server_socket, csocket_t *client_socket);
void server_handler_when_readable(
    server_t *server, ssocket_t *server_socket, csocket_t *client_socket);
void server_handler_when_writable(
    server_t *server, ssocket_t *server_socket, csocket_t *client_socket);

void server_handler_when_readable_state_unknown(
    server_t *server, csocket_t *client_socket, const char *statement);
void server_handler_when_readable_state_player(
    server_t *server, csocket_t *client_socket, const char *statement);
void server_handler_when_readable_state_watcher(
    server_t *server, csocket_t *client_socket, const char *statement);
