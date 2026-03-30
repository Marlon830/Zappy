/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include <sys/types.h>

#include <stdbool.h>
#include <stdint.h>
#include <signal.h>

typedef unsigned char (process_callback_t)(void *context);

typedef pid_t process_t;
typedef struct process_status_s {
    bool running;
    bool paused;

    bool exited;
    uint8_t exit_code;

    bool signaled;
    uint16_t signal;
} process_status_t;

process_t process_current(void);
process_t process_parent(void);

process_t process_spawn(process_callback_t *callback, void *context);
process_status_t process_check(process_t process);

bool process_isrunning(process_t process);
bool process_ispaused(process_t process);

bool process_hasexited(process_t process);
uint8_t process_getexitcode(process_t process);

bool process_hassignaled(process_t process);
uint16_t process_getsignal(process_t process);
void process_sendsignal(process_t process, uint8_t signal);
