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
#include "vglyph-types.h"

#define VGLYPH_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define VGLYPH_MIN(a, b) (((a) < (b)) ? (a) : (b))

#define VGLYPH_CAST(_object, _result) memcpy(&_result, &_object, sizeof(&_result))

vglyph_uint_t
_vglyph_get_device_dpi(void);

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

static inline vglyph_float32_t
_vglyph_degree_to_radians(vglyph_float32_t angle)
{
    const vglyph_float32_t pi = 3.14159265358979323846f;
    const vglyph_float32_t degree_to_radians = pi / 180.0f;

    return angle * degree_to_radians;
}

#endif
