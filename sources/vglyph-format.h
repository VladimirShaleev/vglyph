/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_FORMAT_H
#define VGLYPH_FORMAT_H

#include "vglyph-object.h"

struct _vglyph_format
{
    vglyph_object_t object;
};

void
_vglyph_format_init(vglyph_format_t* format,
                    const vglyph_object_backend_t* object_backend);

void
_vglyph_format_ctor(vglyph_format_t* format);

void
_vglyph_format_dtor(vglyph_format_t* format);

vglyph_bool_t
_vglyph_format_is_cast(vglyph_type_t* type);

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
