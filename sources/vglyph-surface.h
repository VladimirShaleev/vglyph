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
    vglyph_object_t  object;
    const vglyph_surface_backend_t* backend;
    vglyph_format_t* format;
    vglyph_render_t* render;
    vglyph_uint32_t width;
    vglyph_uint32_t height;
    vglyph_uint32_t pitch;
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

static inline void
_vglyph_surface_set_pixel_pos_integer(vglyph_surface_t* surface,
                                      vglyph_sint32_t x,
                                      vglyph_sint32_t y,
                                      const vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    vglyph_render_t* render = surface->render;

    if (color->alpha == 1.0)
    {
        render->backend->set_pixel(render, surface, x, y, color);
    }
    else
    {
        vglyph_float64_t inv_alpha = 1.0 - color->alpha;

        vglyph_color_t prev_color;
        render->backend->get_pixel(render, surface, x, y, &prev_color);

        vglyph_color_t result;
        result.red   = prev_color.red   * inv_alpha + color->red   * color->alpha;
        result.green = prev_color.green * inv_alpha + color->green * color->alpha;
        result.blue  = prev_color.blue  * inv_alpha + color->blue  * color->alpha;
        result.alpha = prev_color.alpha;

        render->backend->set_pixel(render, surface, x, y, &result);
    }
}

static inline void
_vglyph_surface_set_pixel_pos_fractional(vglyph_surface_t* surface,
                                         const vglyph_point_t* point,
                                         const vglyph_color_t* color)
{
    assert(surface);
    assert(point);
    assert(color);

    const vglyph_fixed_t   fixed_1_0   = VGLYPH_FIXED_ONE;
    const vglyph_fixed_t   fixed_1_5   = VGLYPH_FIXED_ONE + (VGLYPH_FIXED_ONE >> 1); 
    const vglyph_fixed_t   fixed_2_0   = VGLYPH_FIXED_ONE << 1; 
    const vglyph_float64_t shift_fract = 1.0 / (VGLYPH_FIXED_ONE * VGLYPH_FIXED_ONE);

    vglyph_fixed_t p_x = _vglyph_fixed_from_float32(point->x);
    vglyph_fixed_t p_y = _vglyph_fixed_from_float32(point->y);

    vglyph_fixed_t p_x_frac = _vglyph_fixed_fractional_part(p_x);
    vglyph_fixed_t p_y_frac = _vglyph_fixed_fractional_part(p_y);

    vglyph_sint32_t ix1 = _vglyph_fixed_to_sint32_floor(p_x);
    vglyph_sint32_t iy1 = _vglyph_fixed_to_sint32_floor(p_y);

    vglyph_fixed_t dx = fixed_1_5 - p_x_frac;
    vglyph_fixed_t dy = fixed_1_5 - p_y_frac;

    vglyph_sint32_t ix2;
    vglyph_sint32_t iy2;

    if (dx > fixed_1_0)
    {
        dx  = fixed_2_0 - dx;
        ix2 = ix1 - 1;
    }
    else
    {
        ix2 = ix1 + 1;
    }

    if (dy > fixed_1_0)
    {
        dy  = fixed_2_0 - dy;
        iy2 = iy1 - 1;
    }
    else
    {
        iy2 = iy1 + 1;
    }

    vglyph_fixed_t xx = fixed_1_0 - dx;
    vglyph_fixed_t yy = fixed_1_0 - dy;

    vglyph_float64_t Sc  = dx * dy * shift_fract;
    vglyph_float64_t Slr = xx * dy * shift_fract;
    vglyph_float64_t Stb = yy * dx * shift_fract;
    vglyph_float64_t Sd  = xx * yy * shift_fract;

    vglyph_color_t result_color;
    result_color.red   = color->red;
    result_color.green = color->green;
    result_color.blue  = color->blue;
    result_color.alpha = color->alpha * Sc;

    _vglyph_surface_set_pixel_pos_integer(surface, ix1, iy1, &result_color);

    if (Sc != 1.0f)
    {
        if (Slr > 0.0f)
        {
            result_color.alpha = color->alpha * Slr;
            _vglyph_surface_set_pixel_pos_integer(surface, ix2, iy1, &result_color);
        }

        if (Stb > 0.0f)
        {
            result_color.alpha = color->alpha * Stb;
            _vglyph_surface_set_pixel_pos_integer(surface, ix1, iy2, &result_color);
        }

        if (Sd > 0.0f)
        {
            result_color.alpha = color->alpha * Sd;
            _vglyph_surface_set_pixel_pos_integer(surface, ix2, iy2, &result_color);
        }
    }
}

static inline vglyph_state_t
_vglyph_surface_add_point(vglyph_vector_t* points, 
                          const vglyph_point_t* point)
{
    assert(points);
    assert(point);

    return _vglyph_vector_add(points, (const vglyph_uint8_t*)point, sizeof(vglyph_point_t));
}

#endif
