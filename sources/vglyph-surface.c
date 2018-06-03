/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"
#include "vglyph-matrix.h"
#include "vglyph-type.h"
#include "vglyph-glyph.h"
#include "vglyph-figure.h"
#include "vglyph-segment-types.h"

static vglyph_point_t* 
_vglyph_surface_offset_point(vglyph_point_t* result,
                             vglyph_surface_t* surface,
                             vglyph_bool_t relative,
                             const vglyph_point_t* offset)
{
    const vglyph_float32_t x = offset->x * surface->width;
    const vglyph_float32_t y = offset->y * surface->height;

    if (relative)
    {
        result->x += x;
        result->y += y;
    }
    else
    {
        result->x = x;
        result->y = y;
    }

    return result;
}

static void 
_vglyph_surface_moveto(vglyph_surface_t* surface,
                       const vglyph_segment_moveto_t* segment,
                       vglyph_bool_t relative,
                       vglyph_point_t* prev_point)
{
    _vglyph_surface_offset_point(prev_point, surface, relative, &segment->point);
}

static void 
_vglyph_surface_lineto(vglyph_surface_t* surface,
                       const vglyph_segment_lineto_t* segment,
                       const vglyph_color_t* color,
                       vglyph_bool_t relative,
                       vglyph_point_t* prev_point)
{
    vglyph_render_t* render = surface->render;

    vglyph_point_t  point = *prev_point;
    vglyph_point_t* end   = _vglyph_surface_offset_point(prev_point, surface, relative, &segment->point);

    vglyph_point_t v;
    _vglyph_point_sub(&v, end, &point);

    const vglyph_float32_t d = 1.0f / _vglyph_point_length(&v);

    vglyph_point_t n;
    _vglyph_point_mul(&n, &v, d);

	for (vglyph_float32_t t = 0.0f; t <= 1.0f; t += d)
	{
		_vglyph_point_add(&point, &point, &n);
        _vglyph_surface_set_pixel_pos_fractional(surface, &point, color);
	}
}

static void
_vglyph_surface_curveto_cubic(vglyph_surface_t* surface,
                              const vglyph_segment_curveto_cubic_t* segment,
                              const vglyph_color_t* color,
                              vglyph_bool_t relative,
                              vglyph_point_t* prev_point)
{
    vglyph_render_t* render = surface->render;

    vglyph_point_t  start  = *prev_point;
    vglyph_point_t  point1 = start;
    vglyph_point_t  point2 = start;
    vglyph_point_t* end    = _vglyph_surface_offset_point(prev_point, surface, relative, &segment->point);

    _vglyph_surface_offset_point(&point1, surface, relative, &segment->point1);
    _vglyph_surface_offset_point(&point2, surface, relative, &segment->point2);
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
                          const vglyph_color_t* color,
                          const vglyph_point_t* position,
                          const vglyph_point_t* origin,
                          vglyph_float32_t radians)
{
    assert(surface);
    assert(glyph);

    //vglyph_matrix_t mat;
    //_vglyph_matrix_identity(&mat);

    //if (origin)
    //    _vglyph_matrix_translate(&mat, &mat, origin->x, origin->y);

    //if (radians != 0.0f)
    //    _vglyph_matrix_rotate(&mat, &mat, radians);

    //if (position)
    //    _vglyph_matrix_translate(&mat, &mat, position->x, position->y);

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
                                       color,
                                       segment_type->segment - VGLYPH_SEGMENT_LINETO_ABS, 
                                       &prev_point);
                break;

            case VGLYPH_SEGMENT_CURVETO_CUBIC_ABS:
            case VGLYPH_SEGMENT_CURVETO_CUBIC_REL:
                _vglyph_surface_curveto_cubic(surface,
                                              (vglyph_segment_curveto_cubic_t*)segment,
                                              color,
                                              segment_type->segment - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS,
                                              &prev_point);
                break;
        }

        offset_segment_type += sizeof(vglyph_segment_type_t);
    }
}
