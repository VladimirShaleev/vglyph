/* vglyph - library for visualize glyphs
 *
 * File: vglyph-glyph.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_GLYPH_H
#define VGLYPH_GLYPH_H

#include "vglyph-object.h"

struct _vglyph_glyph
{
    vglyph_object_t  object;
    vglyph_figure_t* figure;
    vglyph_float32_t horizontal_bearing_x;
    vglyph_float32_t horizontal_bearing_y;
    vglyph_float32_t horizontal_advance;
    vglyph_float32_t vertical_bearing_x;
    vglyph_float32_t vertical_bearing_y;
    vglyph_float32_t vertical_advance;
};

static inline vglyph_glyph_t*
_vglyph_glyph_reference(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return (vglyph_glyph_t*)_vglyph_object_reference(&glyph->object);
}

static inline void
_vglyph_glyph_destroy(vglyph_glyph_t* glyph)
{
    assert(glyph);
    _vglyph_object_destroy(&glyph->object);
}

static inline int
_vglyph_glyph_get_reference_count(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return _vglyph_object_get_reference_count(&glyph->object);
}

static inline vglyph_state_t
_vglyph_glyph_get_state(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return _vglyph_object_get_state(&glyph->object);
}

static inline void
_vglyph_glyph_set_state(vglyph_glyph_t* glyph,
                        vglyph_state_t state)
{
    assert(glyph);
    _vglyph_object_set_state(&glyph->object, state);
}

static inline vglyph_bool_t
_vglyph_glyph_is_valid(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return _vglyph_object_is_valid(&glyph->object);
}

#endif
