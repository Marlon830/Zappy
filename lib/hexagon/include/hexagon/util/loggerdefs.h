/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

/*
 * Yet another oddity of the coding style checker -- using '\e' produces a C-L3
 * error, which makes no sense. So, I'm using the hex value of the escape char
 * used to produce ANSI escape codes.
 */
#define LOGGER_TTYFMT "\x1b[0m\x1b[37m%s %s%9s\x1b[0m \x1b[37m%s\x1b[0m"
#define LOGGER_PUREFMT "%s %.0s%9s %s"

#define LOGGER_PARAMS(STR) dt_str, level->tag_format, level->tag_text, STR
