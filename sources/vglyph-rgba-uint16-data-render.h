/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint16-data-render.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_RGBA_UINT16_RENDER_H
#define VGLYPH_RGBA_UINT16_RENDER_H

#include "vglyph-render.h"

typedef struct _vglyph_rgba_uint16_data_render
{
    vglyph_render_t base;
    vglyph_bool_t   swap_bytes;
} vglyph_rgba_uint16_data_render_t;

void
_vglyph_rgba_uint16_data_render_init(vglyph_rgba_uint16_data_render_t* render,
                                     const vglyph_object_backend_t* object_backend,
                                     const vglyph_render_backend_t* render_backend,
                                     vglyph_rgba_uint_format_t* format);

void
_vglyph_rgba_uint16_data_render_ctor(vglyph_rgba_uint16_data_render_t* render);

void
_vglyph_rgba_uint16_data_render_dtor(vglyph_rgba_uint16_data_render_t* render);

vglyph_bool_t
_vglyph_rgba_uint16_data_render_is_cast(vglyph_type_t* type);

vglyph_type_t*
_vglyph_rgba_uint16_data_render_get_type(void);

vglyph_render_t*
_vglyph_rgba_uint16_data_render_create(vglyph_rgba_uint_format_t* format);

static inline void
_vglyph_rgba_uint16_data_render_set_state(vglyph_rgba_uint16_data_render_t* render,
                                          vglyph_state_t state)
{
    assert(render);
    _vglyph_render_set_state(&render->base, state);
}

static inline vglyph_bool_t
_vglyph_rgba_uint16_data_render_is_valid(vglyph_rgba_uint16_data_render_t* render)
{
    assert(render);
    return _vglyph_render_is_valid(&render->base);
}

static inline void
_vglyph_rgba_uint16_data_render_uint16_to_color(vglyph_render_t* render,
                                                vglyph_rgba_uint_format_t* format,
                                                vglyph_uint16_t data,
                                                vglyph_color_t* color)
{
    assert(render);
    assert(format);
    assert(color);

    if (((vglyph_rgba_uint16_data_render_t*)render)->swap_bytes)
        data = _vglyph_swap_uint16(data);

    const vglyph_uint_t alpha_shift = 0;
    const vglyph_uint_t blue_shift  = format->bit_count.a;
    const vglyph_uint_t green_shift = format->bit_count.b + blue_shift;
    const vglyph_uint_t red_shift   = format->bit_count.g + green_shift;

    vglyph_uint32_t red   = (data >> red_shift  ) & format->capacity.r;
    vglyph_uint32_t green = (data >> green_shift) & format->capacity.g;
    vglyph_uint32_t blue  = (data >> blue_shift ) & format->capacity.b;
    vglyph_uint32_t alpha = (data >> alpha_shift) & format->capacity.a;

    color->red   = 0.0;
    color->green = 0.0;
    color->blue  = 0.0;
    color->alpha = 0.0;

    _vglyph_rgba_uint_data_render_unbind_channel(red,   format->components.r, format->inv_capacity.r, color);
    _vglyph_rgba_uint_data_render_unbind_channel(green, format->components.g, format->inv_capacity.g, color);
    _vglyph_rgba_uint_data_render_unbind_channel(blue,  format->components.b, format->inv_capacity.b, color);
    _vglyph_rgba_uint_data_render_unbind_channel(alpha, format->components.a, format->inv_capacity.a, color);
}

static inline vglyph_uint16_t
_vglyph_rgba_uint16_data_render_color_to_uint16(vglyph_render_t* render,
                                                vglyph_rgba_uint_format_t* format,
                                                const vglyph_color_t* color)
{
    assert(render);
    assert(format);
    assert(color);

    vglyph_uint32_t red   = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.r, format->capacity.r);
    vglyph_uint32_t green = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.g, format->capacity.g);
    vglyph_uint32_t blue  = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.b, format->capacity.b);
    vglyph_uint32_t alpha = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.a, format->capacity.a);

    const vglyph_uint_t alpha_shift = 0;
    const vglyph_uint_t blue_shift  = format->bit_count.a;
    const vglyph_uint_t green_shift = format->bit_count.b + blue_shift;
    const vglyph_uint_t red_shift   = format->bit_count.g + green_shift;

    vglyph_uint16_t result = 
        (red   << red_shift  ) |
        (green << green_shift) | 
        (blue  << blue_shift ) | 
        (alpha << alpha_shift);

    if (((vglyph_rgba_uint16_data_render_t*)render)->swap_bytes)
        result = _vglyph_swap_uint16(result);

    return result;
}

#endif
