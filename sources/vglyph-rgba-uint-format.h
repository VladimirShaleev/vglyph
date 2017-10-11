/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint-format.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_RGBA_UINT_FORMAT_H
#define VGLYPH_RGBA_UINT_FORMAT_H

#include "vglyph-format.h"

typedef struct _vglyph_rgba_uint_capacity
{
    vglyph_uint32_t r;
    vglyph_uint32_t g;
    vglyph_uint32_t b;
    vglyph_uint32_t a;
} vglyph_rgba_uint_capacity_t;

struct _vglyph_rgba_uint_format
{
    vglyph_format_t              base;
    vglyph_packaging_bytes_t     packaging_bytes;
    vglyph_rgba_components_t     components;
    vglyph_rgba_uint_bit_count_t bit_count;
    vglyph_rgba_uint_capacity_t  capacity;
};

void
_vglyph_rgba_uint_format_init(vglyph_rgba_uint_format_t* format,
                              const vglyph_object_backend_t* object_backend,
                              const vglyph_format_backend_t* format_backend,
                              const vglyph_packaging_bytes_t* packaging_bytes,
                              const vglyph_rgba_components_t* components,
                              const vglyph_rgba_uint_bit_count_t* bit_count);

void
_vglyph_rgba_uint_format_ctor(vglyph_rgba_uint_format_t* format);

void
_vglyph_rgba_uint_format_dtor(vglyph_rgba_uint_format_t* format);

vglyph_bool_t
_vglyph_rgba_uint_format_is_cast(vglyph_type_t* type);

static inline void
_vglyph_rgba_uint_format_set_state(vglyph_rgba_uint_format_t* format,
                                   vglyph_state_t state)
{
    assert(format);
    _vglyph_format_set_state(&format->base, state);
}

static inline vglyph_bool_t
_vglyph_rgba_uint_format_is_valid(vglyph_rgba_uint_format_t* format)
{
    assert(format);
    return _vglyph_format_is_valid(&format->base);
}

static inline vglyph_uint32_t
_vglyph_rgba_uint_format_get_capacity(vglyph_uint32_t bit_count)
{
    if (!bit_count)
        return 0;

    const vglyph_uint32_t capacity = ~0;
    const vglyph_uint32_t shift = (sizeof(capacity) << 3) - bit_count;

    return capacity << shift >> shift;
}

#endif
