/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/signal.h"

#include <threads.h>
#include <stdbool.h>

struct hook {
    size_t hook_count;
    bool tripped;
};

static mtx_t process_hookedsignals_mutex;
static struct hook process_hookedsignals[SIGSYS] = {0};

static void signal_hook_handler(int signum)
{
    mtx_lock(&process_hookedsignals_mutex);
    process_hookedsignals[signum].tripped = true;
    mtx_unlock(&process_hookedsignals_mutex);
}

void signal_hook(uint16_t signum)
{
    mtx_lock(&process_hookedsignals_mutex);
    if (process_hookedsignals[signum].hook_count == 0)
        signal(signum, &signal_hook_handler);
    process_hookedsignals[signum].hook_count++;
    mtx_unlock(&process_hookedsignals_mutex);
}

void signal_unhook(uint16_t signum)
{
    mtx_lock(&process_hookedsignals_mutex);
    if (process_hookedsignals[signum].hook_count == 0)
        return;
    process_hookedsignals[signum].hook_count--;
    if (process_hookedsignals[signum].hook_count == 0)
        signal(signum, SIG_DFL);
    mtx_unlock(&process_hookedsignals_mutex);
}

bool signal_hastripped(uint16_t signum)
{
    bool tripped;

    mtx_lock(&process_hookedsignals_mutex);
    tripped = process_hookedsignals[signum].tripped;
    process_hookedsignals[signum].tripped = false;
    mtx_unlock(&process_hookedsignals_mutex);
    return tripped;
}
