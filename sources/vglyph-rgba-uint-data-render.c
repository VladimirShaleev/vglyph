/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint-data-render.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-data-surface.h"
#include "vglyph-rgba-uint-format.h"
#include "vglyph-rgba-uint-data-render.h"
#include "vglyph-type.h"

static vglyph_uint32_t
_vglyph_rgba_uint_data_render_get_pixel_channel(vglyph_uint8_t** p_data,
                                                vglyph_uint32_t* p_offset,
                                                vglyph_uint32_t bit_count)
{
    vglyph_uint32_t channel = 0;

    vglyph_uint8_t* data   = *p_data;
    vglyph_uint32_t offset = *p_offset;

    for (vglyph_uint32_t i = bit_count - 1; i != UINT32_MAX; --i)
    {
        vglyph_uint32_t shift = 8 - offset - 1;
        vglyph_uint32_t bit   = (*data >> shift) & 1;

        channel |= (bit << i);

        if (++offset == 8)
        {
            ++data;
            offset = 0;
        }
    }

    *p_data   = data;
    *p_offset = offset;

    return channel;
}

static void
_vglyph_rgba_uint_data_render_set_pixel_channel(vglyph_uint8_t** p_data,
                                                vglyph_uint32_t* p_offset,
                                                vglyph_uint32_t bit_count,
                                                vglyph_uint32_t channel)
{
    vglyph_uint8_t* data   = *p_data;
    vglyph_uint32_t offset = *p_offset;

    for (vglyph_uint32_t i = bit_count - 1; i != UINT32_MAX; --i)
    {
        vglyph_uint32_t bit = (channel & (1 << i)) >> i;
        vglyph_uint32_t shift = 8 - offset - 1;

        *data &= ~(1 << shift);
        *data |= bit << shift;

        if (++offset == 8)
        {
            ++data;
            offset = 0;
        }
    }

    *p_data   = data;
    *p_offset = offset;
}

void
_vglyph_rgba_uint_data_render_init(vglyph_rgba_uint_data_render_t* render,
                                   const vglyph_object_backend_t* object_backend,
                                   const vglyph_render_backend_t* render_backend)
{
    assert(render);
    assert(object_backend);
    assert(render_backend);

    _vglyph_render_init(&render->base, object_backend, render_backend);
}

void
_vglyph_rgba_uint_data_render_ctor(vglyph_rgba_uint_data_render_t* render)
{
    _vglyph_render_ctor(&render->base);

    if (_vglyph_rgba_uint_data_render_is_valid(render))
    {
    }
}

void
_vglyph_rgba_uint_data_render_dtor(vglyph_rgba_uint_data_render_t* render)
{
    _vglyph_render_dtor(&render->base);
}

vglyph_bool_t
_vglyph_rgba_uint_data_render_is_cast(vglyph_type_t* type)
{
    return _vglyph_rgba_uint_data_render_get_type() == type
        || _vglyph_render_is_cast(type);
}

vglyph_type_t*
_vglyph_rgba_uint_data_render_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_rgba_uint_data_render_is_cast);
    return &type;
}

static void
_vglyph_rgba_uint_data_render_destroy(vglyph_object_t* object)
{
    vglyph_rgba_uint_data_render_t* render = (vglyph_rgba_uint_data_render_t*)object;
    _vglyph_rgba_uint_data_render_dtor(render);

    free(render);
}

static void
_vglyph_rgba_uint_data_render_get_pixel(vglyph_render_t* render,
                                        vglyph_surface_t* surface,
                                        vglyph_sint32_t x,
                                        vglyph_sint32_t y,
                                        vglyph_color_t* color)
{
    vglyph_uint8_t* data = ((vglyph_data_surface_t*)surface)->data;
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)surface->format;

    const vglyph_uint32_t pitch  = surface->pitch;
    const vglyph_uint32_t widht  = surface->width;
    const vglyph_uint32_t height = surface->height;

    const vglyph_uint32_t bits_per_pixel = vglyph_format_get_bits_per_pixel(surface->format);

    if (x >= 0 && (vglyph_uint32_t)x < widht && y >= 0 && (vglyph_uint32_t)y < height)
    {
        vglyph_uint32_t pos_per_bits = (vglyph_uint32_t)x * bits_per_pixel;
        vglyph_uint32_t pos = pos_per_bits >> 3;
        vglyph_uint32_t offset = pos_per_bits - (pos << 3);

        data += y * pitch + pos;

        vglyph_uint32_t red   = _vglyph_rgba_uint_data_render_get_pixel_channel(&data, &offset, format->bit_count.r);
        vglyph_uint32_t green = _vglyph_rgba_uint_data_render_get_pixel_channel(&data, &offset, format->bit_count.g);
        vglyph_uint32_t blue  = _vglyph_rgba_uint_data_render_get_pixel_channel(&data, &offset, format->bit_count.b);
        vglyph_uint32_t alpha = _vglyph_rgba_uint_data_render_get_pixel_channel(&data, &offset, format->bit_count.a);

        color->red   = 0.0;
        color->green = 0.0;
        color->blue  = 0.0;
        color->alpha = 0.0;

        _vglyph_rgba_uint_data_render_unbind_channel(red,   format->components.r, format->inv_capacity.r, color);
        _vglyph_rgba_uint_data_render_unbind_channel(green, format->components.g, format->inv_capacity.g, color);
        _vglyph_rgba_uint_data_render_unbind_channel(blue,  format->components.b, format->inv_capacity.b, color);
        _vglyph_rgba_uint_data_render_unbind_channel(alpha, format->components.a, format->inv_capacity.a, color);
    }
}

static void
_vglyph_rgba_uint_data_render_set_pixel(vglyph_render_t* render,
                                        vglyph_surface_t* surface,
                                        vglyph_sint32_t x,
                                        vglyph_sint32_t y,
                                        const vglyph_color_t* color)
{
    vglyph_uint8_t* data = ((vglyph_data_surface_t*)surface)->data;
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)surface->format;

    const vglyph_uint32_t pitch  = surface->pitch;
    const vglyph_uint32_t widht  = surface->width;
    const vglyph_uint32_t height = surface->height;

    const vglyph_uint32_t bits_per_pixel = vglyph_format_get_bits_per_pixel(surface->format);

    if (x >= 0 && (vglyph_uint32_t)x < widht && y >= 0 && (vglyph_uint32_t)y < height)
    {
        vglyph_uint32_t pos_per_bits = (vglyph_uint32_t)x * bits_per_pixel;
        vglyph_uint32_t pos = pos_per_bits >> 3;
        vglyph_uint32_t offset = pos_per_bits - (pos << 3);

        data += y * pitch + pos;

        vglyph_uint32_t red   = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.r, format->capacity.r);
        vglyph_uint32_t green = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.g, format->capacity.g);
        vglyph_uint32_t blue  = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.b, format->capacity.b);
        vglyph_uint32_t alpha = _vglyph_rgba_uint_data_render_bind_channel(color, format->components.a, format->capacity.a);

        _vglyph_rgba_uint_data_render_set_pixel_channel(&data, &offset, format->bit_count.r, red);
        _vglyph_rgba_uint_data_render_set_pixel_channel(&data, &offset, format->bit_count.g, green);
        _vglyph_rgba_uint_data_render_set_pixel_channel(&data, &offset, format->bit_count.b, blue);
        _vglyph_rgba_uint_data_render_set_pixel_channel(&data, &offset, format->bit_count.a, alpha);
    }
}

static void
_vglyph_rgba_uint_data_render_fill(vglyph_render_t* render,
                                   vglyph_surface_t* surface,
                                   vglyph_sint32_t x,
                                   vglyph_sint32_t y,
                                   vglyph_uint32_t width,
                                   vglyph_uint32_t height,
                                   const vglyph_color_t* color)
{
    vglyph_sint32_t x_start = x < 0 ? 0 : x;
    vglyph_sint32_t y_start = y < 0 ? 0 : y;
    vglyph_sint32_t x_end = (vglyph_sint32_t)(x + width  > surface->width  ? surface->width  : width  + x);
    vglyph_sint32_t y_end = (vglyph_sint32_t)(y + height > surface->height ? surface->height : height + y);

    for (y = y_start; y < y_end; ++y)
    {
        for (x = x_start; x < x_end; ++x)
        {
            _vglyph_rgba_uint_data_render_set_pixel(render, surface, x, y, color);
        }
    }
}

static void
_vglyph_rgba_uint_data_render_alpha_blend(vglyph_render_t* render,
                                          vglyph_surface_t* surface,
                                          vglyph_sint32_t x,
                                          vglyph_sint32_t y,
                                          const vglyph_color_t* color)
{
    if (color->alpha == 1.0)
    {
        _vglyph_rgba_uint_data_render_set_pixel(render, surface, x, y, color);
    }
    else
    {
        const vglyph_float64_t alpha     = color->alpha;
        const vglyph_float64_t inv_alpha = 1.0 - alpha;

        vglyph_color_t dest_color;
        _vglyph_rgba_uint_data_render_get_pixel(render, surface, x, y, &dest_color);

        vglyph_color_t result;
        result.red   = dest_color.red   * inv_alpha + color->red   * alpha;
        result.green = dest_color.green * inv_alpha + color->green * alpha;
        result.blue  = dest_color.blue  * inv_alpha + color->blue  * alpha;
        result.alpha = dest_color.alpha;

        _vglyph_rgba_uint_data_render_set_pixel(render, surface, x, y, &result);
    }
}

static const vglyph_object_backend_t vglyph_rgba_uint_data_render_object_backend = {
    _vglyph_rgba_uint_data_render_get_type,
    _vglyph_rgba_uint_data_render_is_cast,
    _vglyph_rgba_uint_data_render_destroy
};

static const vglyph_render_backend_t vglyph_rgba_uint_data_render_backend = {
    _vglyph_rgba_uint_data_render_fill,
    _vglyph_rgba_uint_data_render_get_pixel,
    _vglyph_rgba_uint_data_render_set_pixel,
    _vglyph_rgba_uint_data_render_alpha_blend
};

vglyph_render_t*
_vglyph_rgba_uint_data_render_create(void)
{
    vglyph_rgba_uint_data_render_t* render = 
        (vglyph_rgba_uint_data_render_t*)malloc(sizeof(vglyph_rgba_uint_data_render_t));

    if (!render)
        return (vglyph_render_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_uint_data_render_init(render, 
                                       &vglyph_rgba_uint_data_render_object_backend,
                                       &vglyph_rgba_uint_data_render_backend);

    _vglyph_rgba_uint_data_render_ctor(render);

    return &render->base;
}
