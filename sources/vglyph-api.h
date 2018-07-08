/* vglyph - library for visualize glyphs
 *
 * File: vglyph-api.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_API_H
#define VGLYPH_API_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined (_MSC_VER) && !defined (VGLYPH_STATIC_BUILD)
# define vglyph_public __declspec(dllexport)
#endif

#if defined (_MSC_VER) && !defined (__cplusplus)
# undef inline
# define inline __inline
#endif

#ifdef __STRICT_ANSI__
# undef inline
# define inline __inline__
#endif

#include "vglyph.h"

#define VGLYPH_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define VGLYPH_MIN(a, b) (((a) < (b)) ? (a) : (b))

static inline vglyph_bool_t
_vglyph_is_little_endian(void)
{
    const vglyph_uint32_t i = 1;
    return *((vglyph_uint8_t*)&i) == 1;
}

static inline vglyph_uint16_t
_vglyph_swap_uint16(vglyph_uint16_t value)
{
    return (value << 8) | (value >> 8);
}

static inline vglyph_uint32_t
_vglyph_swap_uint32(vglyph_uint32_t value)
{
    value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0x00FF00FF);
    value = (value << 16) | (value >> 16);

    return value;
}

#endif
