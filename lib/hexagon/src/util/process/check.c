/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/process.h"

#include <sys/wait.h>

#include <assert.h>

process_status_t process_check(process_t process)
{
    process_status_t process_status;
    int pid_status;

    if (waitpid(process, &pid_status, WNOHANG) < 0) {
        process_status = (process_status_t) {
            .exited = true
        };
        return process_status;
    }
    process_status.paused = WIFSTOPPED(pid_status);
    process_status.exited = WIFEXITED(pid_status);
    process_status.exit_code =
        process_status.exited ? WEXITSTATUS(pid_status) : 0;
    process_status.signaled =
        WIFSIGNALED(pid_status) || WIFSTOPPED(pid_status);
    process_status.signal = process_status.signaled ? WTERMSIG(pid_status) : 0;
    return process_status;
}
