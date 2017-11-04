/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-little-uint-data-render.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-data-surface.h"
#include "vglyph-rgba-uint-format.h"
#include "vglyph-rgba-uint-data-render.h"
#include "vglyph-rgba-little-uint-data-render.h"
#include "vglyph-type.h"

static void
_vglyph_rgba_little_uint_data_render_set_pixel_channel(vglyph_uint8_t* start,
                                                       vglyph_uint8_t** p_data,
                                                       vglyph_uint32_t* p_offset,
                                                       vglyph_uint32_t bit_count,
                                                       vglyph_uint32_t channel,
                                                       vglyph_sint_t packaging_bytes)
{
    vglyph_uint8_t* data   = *p_data;
    vglyph_uint32_t offset = *p_offset;

    vglyph_sint_t byte_number = (data - start) % packaging_bytes;
    vglyph_sint_t byte_offset = (packaging_bytes - 1) - (byte_number << 1);

    vglyph_uint8_t* byte = data + byte_offset;

    for (vglyph_uint32_t i = bit_count - 1; i < UINT32_MAX; --i)
    {
        vglyph_uint32_t bit   = (channel & (1 << i)) >> i;
        vglyph_uint32_t shift = 8 - offset - 1;

        *byte &= ~(1 << shift);
        *byte |= bit << shift;

        if (++offset == 8)
        {
            ++data;
            offset = 0;

            byte_number = (data - start) % packaging_bytes;
            byte_offset = (packaging_bytes - 1) - (byte_number << 1);

            byte = data + byte_offset;
        }
    }

    *p_data   = data;
    *p_offset = offset;
}

void
_vglyph_rgba_little_uint_data_render_init(vglyph_rgba_little_uint_data_render_t* render,
                                          const vglyph_object_backend_t* object_backend,
                                          const vglyph_render_backend_t* render_backend)
{
    assert(render);
    assert(object_backend);
    assert(render_backend);

    _vglyph_render_init(&render->base, object_backend, render_backend);
}

void
_vglyph_rgba_little_uint_data_render_ctor(vglyph_rgba_little_uint_data_render_t* render)
{
    _vglyph_render_ctor(&render->base);

    if (_vglyph_rgba_little_uint_data_render_is_valid(render))
    {
    }
}

void
_vglyph_rgba_little_uint_data_render_dtor(vglyph_rgba_little_uint_data_render_t* render)
{
    _vglyph_render_dtor(&render->base);
}

vglyph_bool_t
_vglyph_rgba_little_uint_data_render_is_cast(vglyph_type_t* type)
{
    return _vglyph_rgba_little_uint_data_render_get_type() == type
        || _vglyph_render_is_cast(type);
}

vglyph_type_t*
_vglyph_rgba_little_uint_data_render_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_rgba_little_uint_data_render_is_cast);
    return &type;
}

static void
_vglyph_rgba_little_uint_data_render_destroy(vglyph_object_t* object)
{
    vglyph_rgba_little_uint_data_render_t* render = (vglyph_rgba_little_uint_data_render_t*)object;
    _vglyph_rgba_little_uint_data_render_dtor(render);

    free(render);
}

static void
_vglyph_rgba_little_uint_data_render_set_pixel(vglyph_render_t* render,
                                               vglyph_surface_t* surface,
                                               vglyph_uint32_t x,
                                               vglyph_uint32_t y,
                                               const vglyph_color_t* color)
{
    vglyph_uint8_t* data = ((vglyph_data_surface_t*)surface)->data;
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)surface->format;

    const vglyph_uint32_t pitch  = surface->pitch;
    const vglyph_uint32_t widht  = surface->width;
    const vglyph_uint32_t height = surface->height;

    const vglyph_uint32_t bits_per_pixel  = vglyph_format_get_bits_per_pixel(surface->format);
    const vglyph_sint_t   packaging_bytes = (vglyph_sint_t)format->base.packaging_bytes.byte_count;

    if (x >= 0 && x < widht && y >= 0 && y < height)
    {
        vglyph_uint32_t pos_per_bits = x * bits_per_pixel;
        vglyph_uint32_t pos = pos_per_bits >> 3;
        vglyph_uint32_t offset = pos_per_bits - (pos << 3);
        vglyph_uint8_t* start = data + y * pitch;

        data = start + pos;

        vglyph_uint32_t red   = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.r, format->capacity.r);
        vglyph_uint32_t green = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.g, format->capacity.g);
        vglyph_uint32_t blue  = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.b, format->capacity.b);
        vglyph_uint32_t alpha = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.a, format->capacity.a);

        _vglyph_rgba_little_uint_data_render_set_pixel_channel(start, &data, &offset, format->bit_count.r, red, packaging_bytes);
        _vglyph_rgba_little_uint_data_render_set_pixel_channel(start, &data, &offset, format->bit_count.g, green, packaging_bytes);
        _vglyph_rgba_little_uint_data_render_set_pixel_channel(start, &data, &offset, format->bit_count.b, blue, packaging_bytes);
        _vglyph_rgba_little_uint_data_render_set_pixel_channel(start, &data, &offset, format->bit_count.a, alpha, packaging_bytes);
    }
}

static void
_vglyph_rgba_little_uint_data_render_fill(vglyph_render_t* render,
                                          vglyph_surface_t* surface,
                                          vglyph_uint32_t x,
                                          vglyph_uint32_t y,
                                          vglyph_uint32_t width,
                                          vglyph_uint32_t height,
                                          const vglyph_color_t* color)
{
    vglyph_uint32_t x_start = x;
    vglyph_uint32_t y_start = y;
    vglyph_uint32_t x_end = y + height > surface->height ? surface->height : height + y;
    vglyph_uint32_t y_end = x + width  > surface->width  ? surface->width  : width  + x;

    for (y = y_start; y < y_end; ++y)
    {
        for (x = x_start; x < x_end; ++x)
        {
            _vglyph_rgba_little_uint_data_render_set_pixel(render, surface, x, y, color);
        }
    }
}

static const vglyph_object_backend_t vglyph_rgba_uint_data_render_object_backend = {
    _vglyph_rgba_little_uint_data_render_get_type,
    _vglyph_rgba_little_uint_data_render_is_cast,
    _vglyph_rgba_little_uint_data_render_destroy
};

static const vglyph_render_backend_t vglyph_rgba_uint_data_render_backend = {
    _vglyph_rgba_little_uint_data_render_fill,
    _vglyph_rgba_little_uint_data_render_set_pixel
};

vglyph_render_t*
_vglyph_rgba_little_uint_data_render_create()
{
    vglyph_rgba_little_uint_data_render_t* render = 
        (vglyph_rgba_little_uint_data_render_t*)malloc(sizeof(vglyph_rgba_little_uint_data_render_t));

    if (!render)
        return (vglyph_render_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_little_uint_data_render_init(render,
                                              &vglyph_rgba_uint_data_render_object_backend,
                                              &vglyph_rgba_uint_data_render_backend);

    _vglyph_rgba_little_uint_data_render_ctor(render);

    return &render->base;
}
