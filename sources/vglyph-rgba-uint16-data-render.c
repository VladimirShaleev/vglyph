﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint16-data-render.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-data-surface.h"
#include "vglyph-rgba-uint-format.h"
#include "vglyph-rgba-uint-data-render.h"
#include "vglyph-rgba-uint16-data-render.h"
#include "vglyph-type.h"

void
_vglyph_rgba_uint16_data_render_init(vglyph_rgba_uint16_data_render_t* render,
                                     const vglyph_object_backend_t* object_backend,
                                     const vglyph_render_backend_t* render_backend)
{
    assert(render);
    assert(object_backend);
    assert(render_backend);

    _vglyph_render_init(&render->base, object_backend, render_backend);
}

void
_vglyph_rgba_uint16_data_render_ctor(vglyph_rgba_uint16_data_render_t* render)
{
    _vglyph_render_ctor(&render->base);

    if (_vglyph_rgba_uint16_data_render_is_valid(render))
    {
    }
}

void
_vglyph_rgba_uint16_data_render_dtor(vglyph_rgba_uint16_data_render_t* render)
{
    _vglyph_render_dtor(&render->base);
}

vglyph_bool_t
_vglyph_rgba_uint16_data_render_is_cast(vglyph_type_t* type)
{
    return _vglyph_rgba_uint16_data_render_get_type() == type
        || _vglyph_render_is_cast(type);
}

vglyph_type_t*
_vglyph_rgba_uint16_data_render_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_rgba_uint16_data_render_is_cast);
    return &type;
}

static void
_vglyph_rgba_uint16_data_render_destroy(vglyph_object_t* object)
{
    vglyph_rgba_uint16_data_render_t* render = (vglyph_rgba_uint16_data_render_t*)object;
    _vglyph_rgba_uint16_data_render_dtor(render);

    free(render);
}

static void
_vglyph_rgba_uint16_data_render_set_pixel(vglyph_render_t* render,
                                          vglyph_surface_t* surface,
                                          vglyph_float32_t x,
                                          vglyph_float32_t y,
                                          const vglyph_color_t* color)
{
    vglyph_uint8_t* data = ((vglyph_data_surface_t*)surface)->data;
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)surface->format;

    const vglyph_uint32_t pitch  = surface->pitch;
    const vglyph_uint32_t widht  = surface->width;
    const vglyph_uint32_t height = surface->height;

    if (x >= 0 && x < widht && y >= 0 && y < height)
    {
        data += (vglyph_uint32_t)y * pitch + ((vglyph_uint32_t)x << 1);

        vglyph_uint32_t red   = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.r, format->capacity.r);
        vglyph_uint32_t green = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.g, format->capacity.g);
        vglyph_uint32_t blue  = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.b, format->capacity.b);
        vglyph_uint32_t alpha = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.a, format->capacity.a);

        const vglyph_uint_t alpha_shift = 0;
        const vglyph_uint_t blue_shift  = format->bit_count.a;
        const vglyph_uint_t green_shift = format->bit_count.b + blue_shift;
        const vglyph_uint_t red_shift   = format->bit_count.g + green_shift;

        const vglyph_uint16_t result = 
            (red   << red_shift  ) |
            (green << green_shift) | 
            (blue  << blue_shift ) | 
            (alpha << alpha_shift);

        if (_vglyph_is_little_endian())
        {
            *data++ = (result >> 8) & 0xFF;
            *data++ = (result >> 0) & 0xFF;
        }
        else
        {
            *((vglyph_uint16_t*)data) = result;
        }
    }
}

static const vglyph_object_backend_t vglyph_rgba_uint16_data_render_object_backend = {
    _vglyph_rgba_uint16_data_render_get_type,
    _vglyph_rgba_uint16_data_render_is_cast,
    _vglyph_rgba_uint16_data_render_destroy
};

static const vglyph_render_backend_t vglyph_rgba_uint16_data_render_backend = {
    _vglyph_rgba_uint16_data_render_set_pixel
};

vglyph_render_t*
_vglyph_rgba_uint16_data_render_create()
{
    vglyph_rgba_uint16_data_render_t* render = 
        (vglyph_rgba_uint16_data_render_t*)malloc(sizeof(vglyph_rgba_uint16_data_render_t));

    if (!render)
        return (vglyph_render_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_uint16_data_render_init(render, 
                                         &vglyph_rgba_uint16_data_render_object_backend,
                                         &vglyph_rgba_uint16_data_render_backend);

    _vglyph_rgba_uint16_data_render_ctor(render);

    return &render->base;
}