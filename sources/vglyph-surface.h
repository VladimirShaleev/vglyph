/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_SURFACE_H
#define VGLYPH_SURFACE_H

#include "vglyph-object.h"

struct _vglyph_surface
{
    vglyph_object_t object;
};

void
_vglyph_surface_init(vglyph_surface_t* surface,
                     vglyph_object_is_cast_func_t is_cast_func,
                     vglyph_object_destroy_func_t destroy_func);

void
_vglyph_surface_ctor(vglyph_surface_t* surface);

void
_vglyph_surface_dtor(vglyph_surface_t* surface);

static inline void
_vglyph_surface_set_state(vglyph_surface_t* surface,
                          vglyph_state_t state)
{
    assert(surface);
    _vglyph_object_set_state(&surface->object, state);
}

static inline vglyph_bool_t
_vglyph_surface_is_valid(vglyph_surface_t* surface)
{
    assert(surface);
    return _vglyph_object_is_valid(&surface->object);
}

static inline vglyph_bool_t
_vglyph_surface_is_cast(vglyph_object_t* object,
                        vglyph_type_t type)
{
    return type == VGLYPH_TYPE_SURFACE ? TRUE : FALSE;
}

#endif
