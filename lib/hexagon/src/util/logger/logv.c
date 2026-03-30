/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"
#include "hexagon/util/loggerdefs.h"

#include "hexagon/util/fmt.h"
#include "hexagon/util/mem.h"
#include "hexagon/util/time.h"

#include <limits.h>

#include <unistd.h>
#include <stdio.h>

struct formattedlog {
    char *formatted_tty;
    char *formatted_pure;
};

static void logger_logv_print(struct formattedlog *context, void *_fd)
{
    int fd = (int) (size_t) _fd;

    dprintf(fd, "%s\n", isatty(fd) ?
        context->formatted_tty : context->formatted_pure);
}

void logger_logv(logger_t *self, const logger_level_t *level,
    const char *format, va_list args)
{
    const char *dt_str = time_formatnow("%Y-%m-%d %H:%M:%S");
    char user_msg[fmt_lengthv(format, args) + 1];
    char fmt_tty[
        fmt_length(LOGGER_TTYFMT, LOGGER_PARAMS("")) + sizeof(user_msg)];
    char fmt_pure[
        fmt_length(LOGGER_PUREFMT, LOGGER_PARAMS("")) + sizeof(user_msg)];
    struct formattedlog context = { fmt_tty, fmt_pure };

    if (level->level < self->level_threshold)
        return;
    vsnprintf(user_msg, sizeof(user_msg), format, args);
    snprintf(fmt_tty, sizeof(fmt_tty),
        LOGGER_TTYFMT, LOGGER_PARAMS(user_msg));
    snprintf(fmt_pure, sizeof(fmt_pure),
        LOGGER_PUREFMT, LOGGER_PARAMS(user_msg));
    LIST_FOREACHC(self->fd_list, &context, &logger_logv_print);
}
