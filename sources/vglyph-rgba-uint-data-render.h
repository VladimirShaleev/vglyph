/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint-data-render.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_RGBA_UINT_RENDER_H
#define VGLYPH_RGBA_UINT_RENDER_H

#include "vglyph-render.h"

typedef struct _vglyph_rgba_uint_data_render
{
    vglyph_render_t base;
} vglyph_rgba_uint_data_render_t;

void
_vglyph_rgba_uint_data_render_init(vglyph_rgba_uint_data_render_t* render,
                                   const vglyph_object_backend_t* object_backend,
                                   const vglyph_render_backend_t* render_backend);

void
_vglyph_rgba_uint_data_render_ctor(vglyph_rgba_uint_data_render_t* render);

void
_vglyph_rgba_uint_data_render_dtor(vglyph_rgba_uint_data_render_t* render);

vglyph_bool_t
_vglyph_rgba_uint_data_render_is_cast(vglyph_type_t* type);

vglyph_type_t*
_vglyph_rgba_uint_data_render_get_type(void);

vglyph_render_t*
_vglyph_rgba_uint_data_render_create(void);

static inline void
_vglyph_rgba_uint_data_render_set_state(vglyph_rgba_uint_data_render_t* render,
                                        vglyph_state_t state)
{
    assert(render);
    _vglyph_render_set_state(&render->base, state);
}

static inline vglyph_bool_t
_vglyph_rgba_uint_data_render_is_valid(vglyph_rgba_uint_data_render_t* render)
{
    assert(render);
    return _vglyph_render_is_valid(&render->base);
}

static inline vglyph_float64_t
_vglyph_rgba_uint_data_render_get_float_channel(vglyph_uint32_t channel,
                                                vglyph_float64_t inv_capacity)
{
    vglyph_float64_t result = channel * inv_capacity;

    if (result > 1.0)
        result = 1.0;

    return result;
}

static inline vglyph_uint32_t
_vglyph_rgba_uint_data_render_get_channel(vglyph_float64_t channel,
                                          vglyph_uint32_t capacity)
{
    if (channel < 0.0)
        channel = 0.0;
    else if (channel > 1.0)
        channel = 1.0;

    return (vglyph_uint32_t)(channel * capacity + 0.5);
}

static inline void
_vglyph_rgba_uint_data_render_unbind_channel(vglyph_uint32_t channel,
                                             vglyph_component_t component,
                                             vglyph_float64_t inv_capacity,
                                             vglyph_color_t* color)
{
    switch (component)
    {
        case VGLYPH_COMPONENT_ZERO:
        case VGLYPH_COMPONENT_ONE:
            break;

        default:
            (&color->red)[component - VGLYPH_COMPONENT_RED] = 
                _vglyph_rgba_uint_data_render_get_float_channel(channel, inv_capacity);
            break;
    }
}

static inline vglyph_uint32_t
_vglyph_rgba_uint_data_render_bind_channel(const vglyph_color_t* color,
                                           vglyph_component_t component,
                                           vglyph_uint32_t capacity)
{
    vglyph_uint32_t bind_channel;

    switch (component)
    {
        case VGLYPH_COMPONENT_ZERO:
            bind_channel = 0;
            break;

        case VGLYPH_COMPONENT_ONE:
            bind_channel = capacity;
            break;

        default:
            bind_channel = _vglyph_rgba_uint_data_render_get_channel(
                (&color->red)[component - VGLYPH_COMPONENT_RED], capacity);
            break;
    }

    return bind_channel;
}

#endif
