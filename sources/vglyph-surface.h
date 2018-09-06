/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.h
 * Copyright (C) 2018 Shaleev Vladimir
 */

#ifndef VGLYPH_SURFACE_H
#define VGLYPH_SURFACE_H

#include "vglyph-object.h"
#include "vglyph-format.h"
#include "vglyph-render.h"
#include "vglyph-vector.h"
#include "vglyph-fixed.h"
#include "vglyph-point.h"

typedef struct _vglyph_surface_backend
{
    vglyph_uint8_t* (*lock)(vglyph_surface_t* surface,
                            vglyph_uint32_t x,
                            vglyph_uint32_t y,
                            vglyph_uint32_t width,
                            vglyph_uint32_t height);
    void (*unlock)(vglyph_surface_t* surface);
} vglyph_surface_backend_t;

struct _vglyph_surface
{
    vglyph_object_t                 object;
    const vglyph_surface_backend_t* backend;
    vglyph_format_t*                format;
    vglyph_render_t*                render;
    vglyph_uint32_t                 width;
    vglyph_uint32_t                 height;
    vglyph_uint32_t                 pitch;
    vglyph_uint32_t                 rasterizer_width;
    vglyph_uint32_t                 rasterizer_height;
};

void
_vglyph_surface_init(vglyph_surface_t* surface,
                     const vglyph_object_backend_t* object_backend,
                     const vglyph_surface_backend_t* surface_backend,
                     vglyph_format_t* format,
                     vglyph_render_t* render,
                     vglyph_uint32_t width,
                     vglyph_uint32_t height,
                     vglyph_uint32_t pitch);

void
_vglyph_surface_ctor(vglyph_surface_t* surface);

void
_vglyph_surface_dtor(vglyph_surface_t* surface);

vglyph_bool_t
_vglyph_surface_is_cast(vglyph_type_t* type);

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

static inline vglyph_state_t
_vglyph_surface_add_point(vglyph_vector_t* points, 
                          const vglyph_point_t* point)
{
    assert(points);
    assert(point);

    return _vglyph_vector_add(points, (const vglyph_uint8_t*)point, sizeof(vglyph_point_t));
}

static inline 
_vglyph_surface_get_default_multisampling(void)
{
    return VGLYPH_MULTISAMPLING_4;
}

#endif
