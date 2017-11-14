/* vglyph - library for visualize glyphs
 *
 * File: vglyph-fixed.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_FIXED_H
#define VGLYPH_FIXED_H

#include "vglyph-api.h"
#include "vglyph-types.h"

#define VGLYPH_FIXED_BITS      32
#define VGLYPH_FIXED_FRAC_BITS 8

#define VGLYPH_FIXED_ONE     ((vglyph_fixed_t)(1 << VGLYPH_FIXED_FRAC_BITS))
#define VGLYPH_FIXED_EPSILON ((vglyph_fixed_t)1);

#define VGLYPH_FIXED_FRAC_MASK  ((vglyph_fixed_t)(((vglyph_uint32_t)(-1)) >> (VGLYPH_FIXED_BITS - VGLYPH_FIXED_FRAC_BITS)))
#define VGLYPH_FIXED_WHOLE_MASK (~VGLYPH_FIXED_FRAC_MASK)

typedef vglyph_sint32_t vglyph_fixed_t;

static inline vglyph_fixed_t
_vglyph_fixed_from_sint32(vglyph_sint32_t value)
{
    return value << VGLYPH_FIXED_FRAC_BITS;
}

static inline vglyph_fixed_t
_vglyph_fixed_from_float32(vglyph_float32_t value)
{
    return (vglyph_fixed_t)floorf(value * VGLYPH_FIXED_ONE + 0.5f);
}

static inline vglyph_sint32_t
_vglyph_fixed_integer_part(vglyph_fixed_t value)
{
    return (value >> VGLYPH_FIXED_FRAC_BITS);
}

static inline vglyph_sint32_t
_vglyph_fixed_fractional_part(vglyph_fixed_t value)
{
    return ((vglyph_sint32_t)(value & VGLYPH_FIXED_FRAC_MASK));
}

static inline vglyph_sint32_t
_vglyph_fixed_to_sint32_floor(vglyph_fixed_t value)
{
    if (value >= 0)
        return value >> VGLYPH_FIXED_FRAC_BITS;
    else
        return -((-value - 1) >> VGLYPH_FIXED_FRAC_BITS) - 1;
}

static inline vglyph_sint32_t
_vglyph_fixed_to_sint32_ceil(vglyph_fixed_t value)
{
    if (value > 0)
        return ((value - 1) >> VGLYPH_FIXED_FRAC_BITS) + 1;
    else
        return -(-value >> VGLYPH_FIXED_FRAC_BITS);
}

static inline vglyph_sint32_t
_vglyph_fixed_to_sint32_round(vglyph_fixed_t value)
{
    return _vglyph_fixed_integer_part(value + ((VGLYPH_FIXED_FRAC_MASK + 1) >> 1));
}

static inline vglyph_sint32_t
_vglyph_fixed_to_sint32_round_down(vglyph_fixed_t value)
{
    return _vglyph_fixed_integer_part(value + (VGLYPH_FIXED_FRAC_MASK >> 1));
}

static inline vglyph_float32_t
_vglyph_fixed_to_float32(vglyph_fixed_t value)
{
    const vglyph_float32_t inv_one_float = 1.0f / VGLYPH_FIXED_ONE;
    return value * inv_one_float;
}

static inline vglyph_bool_t
_vglyph_fixed_is_integer(vglyph_fixed_t value)
{
    return (value & VGLYPH_FIXED_FRAC_MASK) == 0;
}

static inline vglyph_fixed_t
_vglyph_fixed_floor(vglyph_fixed_t value)
{
    return value & VGLYPH_FIXED_WHOLE_MASK;
}

static inline vglyph_fixed_t
_vglyph_fixed_ceil(vglyph_fixed_t value)
{
    return _vglyph_fixed_floor(value + VGLYPH_FIXED_FRAC_MASK);
}

static inline vglyph_fixed_t
_vglyph_fixed_round(vglyph_fixed_t value)
{
    return _vglyph_fixed_floor(value + ((VGLYPH_FIXED_FRAC_MASK + 1) >> 1));
}

static inline vglyph_fixed_t
_vglyph_fixed_round_down(vglyph_fixed_t value)
{
    return _vglyph_fixed_floor(value + (VGLYPH_FIXED_FRAC_MASK >> 1));
}

static inline vglyph_fixed_t
_vglyph_fixed_mul(vglyph_fixed_t a, 
                  vglyph_fixed_t b)
{
    return (vglyph_fixed_t)((vglyph_sint64_t)a * b >> VGLYPH_FIXED_FRAC_BITS);
}

static inline vglyph_fixed_t
_vglyph_fixed_div(vglyph_fixed_t a, 
                  vglyph_fixed_t b)
{
    return (vglyph_fixed_t)(((vglyph_sint64_t)a << VGLYPH_FIXED_FRAC_BITS) / b);
}

static inline vglyph_fixed_t
_vglyph_fixed_mul_div(vglyph_fixed_t a, 
                      vglyph_fixed_t b, 
                      vglyph_fixed_t c)
{
    return (vglyph_fixed_t)((vglyph_sint64_t)a * b / c);
}

#endif
