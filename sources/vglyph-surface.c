/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"
#include "vglyph-type.h"

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

    surface->backend       = surface_backend;
    surface->format        = _vglyph_format_reference(format);
    surface->render        = _vglyph_render_reference(render);
    surface->width         = width;
    surface->height        = height;
    surface->pitch         = pitch;
    surface->multisampling = _vglyph_surface_get_default_multisampling();
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

vglyph_multisampling_t
vglyph_surface_get_multisampling(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->multisampling;

    return VGLYPH_MULTISAMPLING_DEFAULT;
}

void
vglyph_surface_set_multisampling(vglyph_surface_t* surface,
                                 vglyph_multisampling_t quality)
{
    assert(surface);
    assert(quality == VGLYPH_MULTISAMPLING_DEFAULT ||
           quality == VGLYPH_MULTISAMPLING_1       ||
           quality == VGLYPH_MULTISAMPLING_2       ||
           quality == VGLYPH_MULTISAMPLING_4       ||
           quality == VGLYPH_MULTISAMPLING_8       ||
           quality == VGLYPH_MULTISAMPLING_16      ||
           quality == VGLYPH_MULTISAMPLING_32);

    if (_vglyph_surface_is_valid(surface))
    {
        if (quality == VGLYPH_MULTISAMPLING_DEFAULT)
            quality = _vglyph_surface_get_default_multisampling();

        surface->multisampling = quality;
        surface->backend->update_multisampling(surface);
    }
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
        surface->backend->fill(surface, x, y, width, height, color);
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
        surface->backend->get_pixel(surface, x, y, color);
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
        surface->backend->set_pixel(surface, x, y, color);
}

vglyph_bool_t
vglyph_surface_draw_glyph(vglyph_surface_t* surface,
                          vglyph_glyph_t* glyph,
                          vglyph_float32_t pt,
                          const vglyph_color_t* color,
                          const vglyph_point_t* position,
                          const vglyph_point_t* origin,
                          const vglyph_point_t* scale,
                          vglyph_float32_t angle)
{
    assert(surface);
    assert(glyph);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        return surface->backend->draw_glyph(surface,
                                            glyph,
                                            pt,
                                            color,
                                            position,
                                            origin,
                                            scale,
                                            angle);
    }

    return FALSE;
}

vglyph_bool_t
vglyph_surface_draw_glyph_viewport(vglyph_surface_t* surface,
                                   vglyph_glyph_t* glyph,
                                   const vglyph_color_t* color,
                                   const vglyph_point_t* position,
                                   const vglyph_point_t* viewport,
                                   const vglyph_point_t* origin,
                                   const vglyph_point_t* scale,
                                   vglyph_float32_t angle)
{
    assert(surface);
    assert(glyph);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        return surface->backend->draw_glyph_viewport(surface,
                                                     glyph,
                                                     color,
                                                     position,
                                                     viewport,
                                                     origin,
                                                     scale,
                                                     angle);
    }

    return FALSE;
}

vglyph_bool_t
vglyph_surface_draw_glyph_transform(vglyph_surface_t* surface,
                                    vglyph_glyph_t* glyph,
                                    const vglyph_color_t* color,
                                    const vglyph_transform_t* transform)
{
    assert(surface);
    assert(glyph);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        return surface->backend->draw_glyph_transform(surface,
                                                      glyph,
                                                      color,
                                                      transform);
    }

    return FALSE;
}
