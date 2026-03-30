/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/util/logger.h"

/*
 * Yet again, the so called "coding style" makes **ZERO** sense. Why would you
 * be FORCED to declare static struct values like this instead of just being a
 * one liner???
 */
const logger_level_t LL_TRACE = {
    0, "\x1b[35m", "trace" };
const logger_level_t LL_DEBUG = {
    1, "\x1b[95m", "debug" };
const logger_level_t LL_INFO = {
    5, "\x1b[97m", "info" };
const logger_level_t LL_WARN = {
    10, "\x1b[33m", "warning" };
const logger_level_t LL_ERR = {
    15, "\x1b[91m\x1b[1m", "error" };
const logger_level_t LL_FATAL = {
    20, "\x1b[101m\x1b[97m\x1b[1m", "fatal"};
