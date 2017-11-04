/* vglyph - library for visualize glyphs
 *
 * File: vglyph-render.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_RENDER_H
#define VGLYPH_RENDER_H

#include "vglyph-object.h"

typedef struct _vglyph_render vglyph_render_t;

typedef struct _vglyph_render_backend
{
    void (*fill)(vglyph_render_t* render,
                 vglyph_surface_t* surface,
                 vglyph_uint32_t x,
                 vglyph_uint32_t y,
                 vglyph_uint32_t width,
                 vglyph_uint32_t height,
                 const vglyph_color_t* color);
    void (*set_pixel)(vglyph_render_t* render,
                      vglyph_surface_t* surface,
                      vglyph_uint32_t x,
                      vglyph_uint32_t y,
                      const vglyph_color_t* color);
} vglyph_render_backend_t;

struct _vglyph_render
{
    vglyph_object_t object;
    const vglyph_render_backend_t* backend;
};

void
_vglyph_render_init(vglyph_render_t* render,
                    const vglyph_object_backend_t* object_backend,
                    const vglyph_render_backend_t* render_backend);

void
_vglyph_render_ctor(vglyph_render_t* render);

void
_vglyph_render_dtor(vglyph_render_t* render);

vglyph_bool_t
_vglyph_render_is_cast(vglyph_type_t* type);

vglyph_type_t*
_vglyph_render_get_type(void);

static inline vglyph_render_t*
_vglyph_render_reference(vglyph_render_t* render)
{
    assert(render);
    return (vglyph_render_t*)_vglyph_object_reference(&render->object);
}

static inline void
_vglyph_render_destroy(vglyph_render_t* render)
{
    assert(render);
    _vglyph_object_destroy(&render->object);
}

static inline int
_vglyph_render_get_reference_count(vglyph_render_t* render)
{
    assert(render);
    return _vglyph_object_get_reference_count(&render->object);
}

static inline vglyph_state_t
_vglyph_render_get_state(vglyph_render_t* render)
{
    assert(render);
    return _vglyph_object_get_state(&render->object);
}

static inline void
_vglyph_render_set_state(vglyph_render_t* render,
                         vglyph_state_t state)
{
    assert(render);
    _vglyph_object_set_state(&render->object, state);
}

static inline vglyph_bool_t
_vglyph_render_is_valid(vglyph_render_t* render)
{
    assert(render);
    return _vglyph_object_is_valid(&render->object);
}

#endif
