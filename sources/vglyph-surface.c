/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"
#include "vglyph-fixed.h"
#include "vglyph-point.h"
#include "vglyph-matrix.h"
#include "vglyph-type.h"
#include "vglyph-glyph.h"
#include "vglyph-figure.h"
#include "vglyph-segment-types.h"

static void 
_vglyph_surface_moveto(vglyph_surface_t* surface,
                       const vglyph_segment_moveto_t* segment,
                       vglyph_bool_t relative,
                       vglyph_point_t* prev_point)
{
    if (relative)
    {
        prev_point->x += segment->point.x;
        prev_point->y += segment->point.y;
    }
    else
    {
        *prev_point = segment->point;
    }
}

static void
set_pixel(vglyph_surface_t* surface,
		  vglyph_render_t* render,
		  vglyph_sint32_t x,
		  vglyph_sint32_t y,
		  vglyph_float64_t alpha)
{
    vglyph_float64_t inv_alpha = 1.0 - alpha;

    vglyph_color_t prev_color;
    render->backend->get_pixel(render, surface, x, y, &prev_color);

    vglyph_color_t color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;
    color.alpha = 0;

    vglyph_color_t result;
    result.red = prev_color.red * inv_alpha + color.red * alpha;
    result.green = prev_color.green * inv_alpha + color.green * alpha;
    result.blue = prev_color.blue * inv_alpha + color.blue * alpha;
    result.alpha = prev_color.alpha;

    render->backend->set_pixel(render, surface, x, y, &result);
}

static void 
_vglyph_surface_lineto(vglyph_surface_t* surface,
                       const vglyph_segment_lineto_t* segment,
                       vglyph_bool_t relative,
                       vglyph_point_t* prev_point)
{
    vglyph_point_t start = *prev_point;

    if (relative)
    {
        prev_point->x += segment->point.x;
        prev_point->y += segment->point.y;
    }
    else
    {
        *prev_point = segment->point;
    }

    vglyph_render_t* render = surface->render;
    vglyph_uint32_t  width  = surface->width;
    vglyph_uint32_t  height = surface->height;

    vglyph_point_t end = *prev_point;

    start.x *= width;
    start.y *= height;
    end.x   *= width;
    end.y   *= height;

    vglyph_point_t v;
    vglyph_point_t p;
    _vglyph_point_sub(&v, &end, &start);

    vglyph_float32_t d = 1.0f / _vglyph_point_length(&v);

	for (vglyph_float32_t t = 0.0f; t <= 1.0f; t += d)
	{
		_vglyph_point_add(&p, _vglyph_point_mul(&p, &v, t), &start);

		vglyph_fixed_t p_x = _vglyph_fixed_from_float32(p.x);
		vglyph_fixed_t p_y = _vglyph_fixed_from_float32(p.y);

		vglyph_fixed_t p_x_frac = _vglyph_fixed_fractional_part(p_x);
		vglyph_fixed_t p_y_frac = _vglyph_fixed_fractional_part(p_y);

		vglyph_sint32_t ix1 = _vglyph_fixed_to_sint32_floor(p_x);
		vglyph_sint32_t iy1 = _vglyph_fixed_to_sint32_floor(p_y);

		vglyph_fixed_t dx = _vglyph_fixed_from_float32(1.5f) - p_x_frac;
		vglyph_fixed_t dy = _vglyph_fixed_from_float32(1.5f) - p_y_frac;

		vglyph_sint32_t ix2;
		vglyph_sint32_t iy2;

		if (dx > 256)
		{
			dx = (VGLYPH_FIXED_ONE << 1) - dx;
			ix2 = ix1 - 1;
		}
		else
		{
			ix2 = ix1 + 1;
		}

		if (dy > 256)
		{
			dy = (VGLYPH_FIXED_ONE << 1) - dy;
			iy2 = iy1 - 1;
		}
		else
		{
			iy2 = iy1 + 1;
		}

		vglyph_fixed_t xx = VGLYPH_FIXED_ONE - dx;
		vglyph_fixed_t yy = VGLYPH_FIXED_ONE - dy;

		vglyph_float64_t Sc = dx * dy / 256.0 / 256.0;
		vglyph_float64_t Slr = xx * dy / 256.0 / 256.0;
		vglyph_float64_t Stb = yy * dx / 256.0 / 256.0;
		vglyph_float64_t Sd = xx * yy / 256.0 / 256.0;

		set_pixel(surface, render, ix1, iy1, Sc);

		if (Sc != 1.0f)
		{
			if (Slr > 0.0f)
				set_pixel(surface, render, ix2, iy1, Slr);

			if (Stb > 0.0f)
				set_pixel(surface, render, ix1, iy2, Stb);

			if (Sd > 0.0f)
				set_pixel(surface, render, ix2, iy2, Sd);
		}
	}
}

void
_vglyph_surface_init(vglyph_surface_t* surface,
                     const vglyph_object_backend_t* object_backend,
                     const vglyph_surface_backend_t* surface_backend,
                     vglyph_format_t* format,
                     vglyph_render_t* render,
                     vglyph_uint32_t width,
                     vglyph_uint32_t height,
                     vglyph_uint32_t pitch)
{
    assert(surface);
    assert(object_backend);
    assert(surface_backend);
    assert(format);
    assert(render);

    _vglyph_object_init(&surface->object, object_backend);

    surface->backend = surface_backend;
    surface->format  = _vglyph_format_reference(format);
    surface->render  = _vglyph_render_reference(render);
    surface->width   = width;
    surface->height  = height;
    surface->pitch   = pitch;
}

void
_vglyph_surface_ctor(vglyph_surface_t* surface)
{
    if (!_vglyph_format_is_valid(surface->format))
    {
        _vglyph_surface_set_state(surface, _vglyph_format_get_state(surface->format));
        return;
    }

    if (!_vglyph_render_is_valid(surface->render))
    {
        _vglyph_surface_set_state(surface, _vglyph_render_get_state(surface->render));
        return;
    }
}

void
_vglyph_surface_dtor(vglyph_surface_t* surface)
{
    _vglyph_render_destroy(surface->render);
    _vglyph_format_destroy(surface->format);
}

vglyph_bool_t
_vglyph_surface_is_cast(vglyph_type_t* type)
{
    return vglyph_get_surface_type() == type;
}

static void
_vglyph_surface_destroy(vglyph_object_t* object)
{
    vglyph_surface_t* surface = (vglyph_surface_t*)object;
    _vglyph_surface_dtor(surface);

    free(surface);
}

static const vglyph_object_backend_t vglyph_surface_object_backend = {
    vglyph_get_surface_type,
    _vglyph_surface_is_cast,
    _vglyph_surface_destroy
};

vglyph_type_t*
vglyph_get_surface_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_surface_is_cast);
    return &type;
}

vglyph_surface_t*
vglyph_object_to_surface(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_surface_t*)_vglyph_object_to_type(object, vglyph_get_surface_type());
}

vglyph_object_t*
vglyph_surface_to_object(vglyph_surface_t* surface)
{
    assert(surface);
    return &surface->object;
}

vglyph_format_t*
vglyph_surface_get_format(vglyph_surface_t* surface)
{
    assert(surface);
    return _vglyph_format_reference(surface->format);
}

vglyph_uint32_t
vglyph_surface_get_width(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->width;

    return 0;
}

vglyph_uint32_t
vglyph_surface_get_height(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->height;

    return 0;
}

vglyph_uint32_t
vglyph_surface_get_pitch(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->pitch;

    return 0;
}

vglyph_uint8_t*
vglyph_surface_lock(vglyph_surface_t* surface,
                    vglyph_uint32_t x,
                    vglyph_uint32_t y,
                    vglyph_uint32_t width,
                    vglyph_uint32_t height)
{
    assert(surface);
    assert(x >= 0);
    assert(y >= 0);
    assert(x + width <= surface->width);
    assert(y + height <= surface->height);

    if (_vglyph_surface_is_valid(surface))
        return surface->backend->lock(surface, x, y, width, height);

    return NULL;
}

void
vglyph_surface_unlock(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        surface->backend->unlock(surface);
}

void
vglyph_surface_fill(vglyph_surface_t* surface,
                    vglyph_uint32_t x,
                    vglyph_uint32_t y,
                    vglyph_uint32_t width,
                    vglyph_uint32_t height,
                    const vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        vglyph_render_t* render = surface->render;
        render->backend->fill(render, surface, x, y, width, height, color);
    }
}

void
vglyph_surface_get_pixel(vglyph_surface_t* surface,
                         vglyph_sint32_t x,
                         vglyph_sint32_t y,
                         vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        vglyph_render_t* render = surface->render;
        render->backend->get_pixel(render, surface, x, y, color);
    }
}

void
vglyph_surface_set_pixel(vglyph_surface_t* surface,
                         vglyph_sint32_t x,
                         vglyph_sint32_t y,
                         const vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        vglyph_render_t* render = surface->render;
        render->backend->set_pixel(render, surface, x, y, color);
    }
}

void
vglyph_surface_draw_glyph(vglyph_surface_t* surface,
                          vglyph_glyph_t* glyph,
                          const vglyph_point_t* position,
                          const vglyph_point_t* origin)
{
    assert(surface);
    assert(glyph);

    const vglyph_segment_type_t* segment_type;
    const void* segment;

    const vglyph_uint_t segment_count = glyph->figure->segment_count;
    vglyph_uint_t offset_segment_type = 0;

    vglyph_point_t prev_point;
    prev_point.x = 0.0f;
    prev_point.y = 0.0f;

    for (vglyph_uint_t i = 0; i < segment_count; ++i)
    {
        segment_type = (vglyph_segment_type_t*)
            _vglyph_vector_at(glyph->figure->segment_types, offset_segment_type);

        segment = _vglyph_vector_at(glyph->figure->segments, segment_type->offset);   

        switch (segment_type->segment)
        {
            case VGLYPH_SEGMENT_CLOSEPATH:
                break;

            case VGLYPH_SEGMENT_MOVETO_ABS:
            case VGLYPH_SEGMENT_MOVETO_REL:
                _vglyph_surface_moveto(surface,
                                       (vglyph_segment_moveto_t*)segment, 
                                       segment_type->segment - VGLYPH_SEGMENT_MOVETO_ABS, 
                                       &prev_point);
                break;

            case VGLYPH_SEGMENT_LINETO_ABS:
            case VGLYPH_SEGMENT_LINETO_REL:
                _vglyph_surface_lineto(surface,
                                       (vglyph_segment_lineto_t*)segment, 
                                       segment_type->segment - VGLYPH_SEGMENT_LINETO_ABS, 
                                       &prev_point);
                break;
        }

        offset_segment_type += sizeof(vglyph_segment_type_t);
    }
}
