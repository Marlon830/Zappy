/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#include "hexagon/util/list.h"

#include <stdarg.h>

typedef struct logger_level_s {
    int level;
    const char *tag_format;
    const char *tag_text;
} logger_level_t;

extern const logger_level_t LL_TRACE;
extern const logger_level_t LL_DEBUG;
extern const logger_level_t LL_INFO;
extern const logger_level_t LL_WARN;
extern const logger_level_t LL_ERR;
extern const logger_level_t LL_FATAL;

typedef struct logger_s {
    int level_threshold;
    list_t *fd_list;
} logger_t;

logger_t *logger_new(const logger_level_t *level);
void logger_delete(logger_t *self);

void logger_setthreshold(logger_t *self, const logger_level_t *level);
int logger_getthreshold(logger_t *self);

void logger_addfd(logger_t *self, int fd);
void logger_removefd(logger_t *self, int fd);

const logger_level_t *logger_findlevel(const char *level_name);

void logger_logv(logger_t *self, const logger_level_t *level,
    const char *format, va_list args);
void logger_log(logger_t *self, const logger_level_t *level,
    const char *format, ...);

void logger_tracev(logger_t *self, const char *format, va_list args);
void logger_trace(logger_t *self, const char *format, ...);

void logger_debugv(logger_t *self, const char *format, va_list args);
void logger_debug(logger_t *self, const char *format, ...);

void logger_infov(logger_t *self, const char *format, va_list args);
void logger_info(logger_t *self, const char *format, ...);

void logger_warnv(logger_t *self, const char *format, va_list args);
void logger_warn(logger_t *self, const char *format, ...);

void logger_errv(logger_t *self, const char *format, va_list args);
void logger_err(logger_t *self, const char *format, ...);

void logger_fatalv(logger_t *self, const char *format, va_list args);
void logger_fatal(logger_t *self, const char *format, ...);

#define LOGGER_LOG(S, LEVEL, MSG, ...) logger_##LEVEL(S, MSG, ##__VA_ARGS__)
