/* vglyph - library for visualize glyphs
 *
 * File: vglyph-data-surface.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_DATA_SURFACE_H
#define VGLYPH_DATA_SURFACE_H

#include "vglyph-surface.h"

typedef struct _vglyph_data_surface
{
    vglyph_surface_t base;
    vglyph_uint8_t*  data;
} vglyph_data_surface_t;

void
_vglyph_data_surface_init(vglyph_data_surface_t* surface,
                          const vglyph_object_backend_t* object_backend,
                          const vglyph_surface_backend_t* surface_backend,
                          vglyph_format_t* format,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height,
                          vglyph_uint32_t pitch,
                          vglyph_uint8_t* data);

void
_vglyph_data_surface_ctor(vglyph_data_surface_t* surface);

void
_vglyph_data_surface_dtor(vglyph_data_surface_t* surface);

vglyph_bool_t
_vglyph_data_surface_is_cast(vglyph_type_t* type);

vglyph_type_t*
_vglyph_data_surface_get_type(void);

static inline void
_vglyph_data_surface_set_state(vglyph_data_surface_t* surface,
                               vglyph_state_t state)
{
    assert(surface);
    _vglyph_surface_set_state(&surface->base, state);
}

static inline vglyph_bool_t
_vglyph_data_surface_is_valid(vglyph_data_surface_t* surface)
{
    assert(surface);
    return _vglyph_surface_is_valid(&surface->base);
}

#endif
