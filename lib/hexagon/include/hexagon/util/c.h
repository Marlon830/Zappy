/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#pragma once

#define UNUSED __attribute__((unused))
#define INLINED __attribute__((always_inline))
#define PACKED __attribute__((packed))

/*
 * Use it ONLY for function pointers -- very error prone, but leverages the
 * tedious work of rewriting the function pointer signature cast every time.
 */
#define FUNC (void *)

#define CALL_IFSET(FN) if (FN) (FN)
