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
                     const vglyph_object_backend_t* object_backend);

void
_vglyph_surface_ctor(vglyph_surface_t* surface);

void
_vglyph_surface_dtor(vglyph_surface_t* surface);

vglyph_bool_t
_vglyph_surface_is_cast(vglyph_uuid_t* uuid);

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

#endif
