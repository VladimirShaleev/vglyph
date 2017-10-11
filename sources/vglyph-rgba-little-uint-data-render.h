/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-little-uint-data-render.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_RGBA_LITTLE_UINT_RENDER_H
#define VGLYPH_RGBA_LITTLE_UINT_RENDER_H

#include "vglyph-render.h"

typedef struct _vglyph_rgba_little_uint_data_render
{
    vglyph_render_t base;
} vglyph_rgba_little_uint_data_render_t;

void
_vglyph_rgba_little_uint_data_render_init(vglyph_rgba_little_uint_data_render_t* render,
                                          const vglyph_object_backend_t* object_backend,
                                          const vglyph_render_backend_t* render_backend);

void
_vglyph_rgba_little_uint_data_render_ctor(vglyph_rgba_little_uint_data_render_t* render);

void
_vglyph_rgba_little_uint_data_render_dtor(vglyph_rgba_little_uint_data_render_t* render);

vglyph_bool_t
_vglyph_rgba_little_uint_data_render_is_cast(vglyph_type_t* type);

vglyph_type_t*
_vglyph_rgba_little_uint_data_render_get_type(void);

vglyph_render_t*
_vglyph_rgba_little_uint_data_render_create(void);

static inline void
_vglyph_rgba_little_uint_data_render_set_state(vglyph_rgba_little_uint_data_render_t* render,
                                               vglyph_state_t state)
{
    assert(render);
    _vglyph_render_set_state(&render->base, state);
}

static inline vglyph_bool_t
_vglyph_rgba_little_uint_data_render_is_valid(vglyph_rgba_little_uint_data_render_t* render)
{
    assert(render);
    return _vglyph_render_is_valid(&render->base);
}

#endif
