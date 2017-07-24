/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_FORMAT_H
#define VGLYPH_FORMAT_H

#include "vglyph-object.h"

typedef struct _vglyph_format_backend
{
    vglyph_uint32_t (*get_bits_per_pixel)(vglyph_format_t* format);
} vglyph_format_backend_t;

struct _vglyph_format
{
    vglyph_object_t object;
    const vglyph_format_backend_t* backend;
};

void
_vglyph_format_init(vglyph_format_t* format,
                    const vglyph_object_backend_t* object_backend,
                    const vglyph_format_backend_t* format_backend);

void
_vglyph_format_ctor(vglyph_format_t* format);

void
_vglyph_format_dtor(vglyph_format_t* format);

vglyph_bool_t
_vglyph_format_is_cast(vglyph_type_t* type);

static inline vglyph_format_t*
_vglyph_format_reference(vglyph_format_t* format)
{
    assert(format);
    return (vglyph_format_t*)_vglyph_object_reference(&format->object);
}

static inline void
_vglyph_format_destroy(vglyph_format_t* format)
{
    assert(format);
    _vglyph_object_destroy(&format->object);
}

static inline int
_vglyph_format_get_reference_count(vglyph_format_t* format)
{
    assert(format);
    return _vglyph_object_get_reference_count(&format->object);
}

static inline vglyph_state_t
_vglyph_format_get_state(vglyph_format_t* format)
{
    assert(format);
    return _vglyph_object_get_state(&format->object);
}

static inline void
_vglyph_format_set_state(vglyph_format_t* format,
                         vglyph_state_t state)
{
    assert(format);
    _vglyph_object_set_state(&format->object, state);
}

static inline vglyph_bool_t
_vglyph_format_is_valid(vglyph_format_t* format)
{
    assert(format);
    return _vglyph_object_is_valid(&format->object);
}

#endif
