/* vglyph - library for visualize glyphs
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
                                     const vglyph_render_backend_t* render_backend,
                                     vglyph_rgba_uint_format_t* format)
{
    assert(render);
    assert(object_backend);
    assert(render_backend);
    assert(format);

    _vglyph_render_init(&render->base, object_backend, render_backend);

    const vglyph_bool_t machine_little_endian = _vglyph_is_little_endian();
    const vglyph_bool_t format_little_endian = 
        (format->base.packaging_bytes.endianness == VGLYPH_ENDIANNESS_HOST && machine_little_endian) ||
        (format->base.packaging_bytes.endianness == VGLYPH_ENDIANNESS_LITTLE);

    render->swap_bytes = 
        ( format_little_endian && !machine_little_endian) || 
        (!format_little_endian &&  machine_little_endian);
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
_vglyph_rgba_uint16_data_render_fill(vglyph_render_t* render,
                                     vglyph_surface_t* surface,
                                     vglyph_sint32_t x,
                                     vglyph_sint32_t y,
                                     vglyph_uint32_t width,
                                     vglyph_uint32_t height,
                                     const vglyph_color_t* color)
{
    vglyph_uint16_t* data = (vglyph_uint16_t*)((vglyph_data_surface_t*)surface)->data;
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)surface->format;

    const vglyph_uint32_t pitch  = surface->pitch >> 1;
    const vglyph_uint16_t result = _vglyph_rgba_uint16_data_render_color_to_uint16(render, format, color);

    vglyph_sint32_t x_start = x < 0 ? 0 : x;
    vglyph_sint32_t y_start = y < 0 ? 0 : y;
    vglyph_sint32_t x_end = (vglyph_sint32_t)(y + height > surface->height ? surface->height : height + y);
    vglyph_sint32_t y_end = (vglyph_sint32_t)(x + width  > surface->width  ? surface->width  : width  + x);

    data += y_start * pitch;

    for (y = y_start; y < y_end; ++y)
    {
        for (x = x_start; x < x_end; ++x)
            *(data + x) = result;

        data += pitch;
    }
}

static void
_vglyph_rgba_uint16_data_render_get_pixel(vglyph_render_t* render,
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

    if (x >= 0 && (vglyph_uint32_t)x < widht && y >= 0 && (vglyph_uint32_t)y < height)
    {
        _vglyph_rgba_uint16_data_render_uint16_to_color(
            render, format, *((vglyph_uint16_t*)(data + y * pitch) + x), color);
    }
}

static void
_vglyph_rgba_uint16_data_render_set_pixel(vglyph_render_t* render,
                                          vglyph_surface_t* surface,
                                          vglyph_sint32_t x,
                                          vglyph_sint32_t y,
                                          const vglyph_color_t* color)
{
    vglyph_rgba_uint16_data_render_t* uint16_data_render = (vglyph_rgba_uint16_data_render_t*)render;
    vglyph_uint8_t* data = ((vglyph_data_surface_t*)surface)->data;
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)surface->format;
    
    const vglyph_uint32_t pitch  = surface->pitch;
    const vglyph_uint32_t widht  = surface->width;
    const vglyph_uint32_t height = surface->height;

    if (x >= 0 && (vglyph_uint32_t)x < widht && y >= 0 && (vglyph_uint32_t)y < height)
    {
        *((vglyph_uint16_t*)(data + y * pitch) + x) = 
            _vglyph_rgba_uint16_data_render_color_to_uint16(render, format, color);
    }
}

static void
_vglyph_rgba_uint16_data_render_alpha_blend(vglyph_render_t* render,
                                            vglyph_surface_t* surface,
                                            vglyph_sint32_t x,
                                            vglyph_sint32_t y,
                                            const vglyph_color_t* color)
{
    if (color->alpha == 1.0)
    {
        _vglyph_rgba_uint16_data_render_set_pixel(render, surface, x, y, color);
    }
    else
    {
        const vglyph_float64_t alpha     = color->alpha;
        const vglyph_float64_t inv_alpha = 1.0 - alpha;

        vglyph_color_t dest_color;
        _vglyph_rgba_uint16_data_render_get_pixel(render, surface, x, y, &dest_color);

        vglyph_color_t result;
        result.red   = dest_color.red   * inv_alpha + color->red   * alpha;
        result.green = dest_color.green * inv_alpha + color->green * alpha;
        result.blue  = dest_color.blue  * inv_alpha + color->blue  * alpha;
        result.alpha = dest_color.alpha;

        _vglyph_rgba_uint16_data_render_set_pixel(render, surface, x, y, &result);
    }
}

static const vglyph_object_backend_t vglyph_rgba_uint16_data_render_object_backend = {
    _vglyph_rgba_uint16_data_render_get_type,
    _vglyph_rgba_uint16_data_render_is_cast,
    _vglyph_rgba_uint16_data_render_destroy
};

static const vglyph_render_backend_t vglyph_rgba_uint16_data_render_backend = {
    _vglyph_rgba_uint16_data_render_fill,
    _vglyph_rgba_uint16_data_render_get_pixel,
    _vglyph_rgba_uint16_data_render_set_pixel,
    _vglyph_rgba_uint16_data_render_alpha_blend
};

vglyph_render_t*
_vglyph_rgba_uint16_data_render_create(vglyph_rgba_uint_format_t* format)
{
    vglyph_rgba_uint16_data_render_t* render = 
        (vglyph_rgba_uint16_data_render_t*)malloc(sizeof(vglyph_rgba_uint16_data_render_t));

    if (!render)
        return (vglyph_render_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_uint16_data_render_init(render, 
                                         &vglyph_rgba_uint16_data_render_object_backend,
                                         &vglyph_rgba_uint16_data_render_backend,
                                         format);

    _vglyph_rgba_uint16_data_render_ctor(render);

    return &render->base;
}
