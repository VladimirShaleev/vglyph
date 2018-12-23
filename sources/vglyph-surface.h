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
#include "vglyph-point.h"

typedef struct _vglyph_surface_backend
{
    void (*update_multisampling)(vglyph_surface_t* surface);
    vglyph_uint8_t* (*lock)(vglyph_surface_t* surface,
                            vglyph_uint32_t x,
                            vglyph_uint32_t y,
                            vglyph_uint32_t width,
                            vglyph_uint32_t height);
    void (*unlock)(vglyph_surface_t* surface);
    void (*fill)(vglyph_surface_t* surface,
                 vglyph_uint32_t x,
                 vglyph_uint32_t y,
                 vglyph_uint32_t width,
                 vglyph_uint32_t height,
                 const vglyph_color_t* color);
    void (*get_pixel)(vglyph_surface_t* surface,
                      vglyph_sint32_t x,
                      vglyph_sint32_t y,
                      vglyph_color_t* color);
    void (*set_pixel)(vglyph_surface_t* surface,
                      vglyph_sint32_t x,
                      vglyph_sint32_t y,
                      const vglyph_color_t* color);
    vglyph_uint_t (*get_dpi)(vglyph_surface_t* surface);
    vglyph_bool_t (*draw_glyph)(vglyph_surface_t* surface,
                                vglyph_glyph_t* glyph,
                                vglyph_float32_t pt,
                                const vglyph_color_t* color,
                                const vglyph_point_t* position,
                                const vglyph_point_t* origin,
                                const vglyph_point_t* scale,
                                vglyph_float32_t angle);
    vglyph_bool_t (*draw_glyph_viewport)(vglyph_surface_t* surface,
                                         vglyph_glyph_t* glyph,
                                         const vglyph_color_t* color,
                                         const vglyph_point_t* position,
                                         const vglyph_point_t* viewport,
                                         const vglyph_point_t* origin,
                                         const vglyph_point_t* scale,
                                         vglyph_float32_t angle);
    vglyph_bool_t (*draw_glyph_transform)(vglyph_surface_t* surface,
                                          vglyph_glyph_t* glyph,
                                          const vglyph_color_t* color,
                                          const vglyph_transform_t* transform);
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
    vglyph_multisampling_t          multisampling;
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

static inline vglyph_multisampling_t
_vglyph_surface_get_default_multisampling(void)
{
    return VGLYPH_MULTISAMPLING_4;
}

#endif
