/* vglyph - library for visualize glyphs
 *
 * File: vglyph-point.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_POINT_H
#define VGLYPH_POINT_H

#include "vglyph-api.h"
#include "vglyph-types.h"

static inline vglyph_point_t*
_vglyph_point_from_coord(vglyph_point_t* result,
                         vglyph_float32_t x, 
                         vglyph_float32_t y)
{
    assert(result);

    result->x = x;
    result->y = y;

    return result;
}

static inline vglyph_point_t*
_vglyph_point_add(vglyph_point_t* result,
                  const vglyph_point_t* a,
                  const vglyph_point_t* b)
{
    assert(result);
    assert(a);
    assert(b);

    result->x = a->x + b->x;
    result->y = a->y + b->y;

    return result;
}

static inline vglyph_point_t*
_vglyph_point_sub(vglyph_point_t* result,
                  const vglyph_point_t* a,
                  const vglyph_point_t* b)
{
    assert(result);
    assert(a);
    assert(b);

    result->x = a->x - b->x;
    result->y = a->y - b->y;

    return result;
}

static inline vglyph_point_t*
_vglyph_point_mul(vglyph_point_t* result,
                  const vglyph_point_t* a,
                  vglyph_float32_t b)
{
    assert(result);
    assert(a);

    result->x = a->x * b;
    result->y = a->y * b;

    return result;
}

static inline vglyph_point_t*
_vglyph_point_div(vglyph_point_t* result,
                  const vglyph_point_t* a,
                  vglyph_float32_t b)
{
    assert(result);
    assert(a);

    vglyph_float32_t inv_b = 1.0f / b;

    result->x = a->x * inv_b;
    result->y = a->y * inv_b;

    return result;
}

static inline vglyph_float32_t
_vglyph_point_dot(const vglyph_point_t* a,
                  const vglyph_point_t* b)
{
    assert(a);
    assert(b);

    return a->x * b->x + a->y + b->y;
}

static inline vglyph_float32_t
_vglyph_point_length_square(const vglyph_point_t* a)
{
    assert(a);

    return a->x * a->x + a->y * a->y;
}

static inline vglyph_float32_t
_vglyph_point_length(const vglyph_point_t* a)
{
    assert(a);

    return sqrtf(_vglyph_point_length_square(a));
}

static inline vglyph_point_t*
_vglyph_point_normalize(vglyph_point_t* result,
                        const vglyph_point_t* a)
{
    assert(result);
    assert(a);

    vglyph_float32_t inv_length = 1.0f / _vglyph_point_length(a);

    result->x = a->x * inv_length;
    result->y = a->y * inv_length;

    return result;
}

static inline vglyph_point_t*
_vglyph_point_min(vglyph_point_t* result,
                  const vglyph_point_t* a,
                  const vglyph_point_t* b)
{
    assert(result);
    assert(a);
    assert(b);

    result->x = min(a->x, b->x);
    result->y = min(a->y, b->y);

    return result;
}

static inline vglyph_point_t*
_vglyph_point_max(vglyph_point_t* result,
                  const vglyph_point_t* a,
                  const vglyph_point_t* b)
{
    assert(result);
    assert(a);
    assert(b);

    result->x = max(a->x, b->x);
    result->y = max(a->y, b->y);

    return result;
}

#endif
