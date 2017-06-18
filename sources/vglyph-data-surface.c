/* vglyph - library for visualize glyphs
 *
 * File: vglyph-data-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-data-surface.h"
#include "vglyph-type.h"

void
_vglyph_data_surface_init(vglyph_data_surface_t* surface,
                          const vglyph_object_backend_t* object_backend,
                          const vglyph_surface_backend_t* surface_backend,
                          vglyph_format_t* format,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height,
                          vglyph_uint32_t pitch,
                          vglyph_uint8_t* data)
{
    assert(data);

    _vglyph_surface_init(&surface->base, 
                         object_backend, 
                         surface_backend,
                         format, 
                         width, 
                         height, 
                         pitch);

    surface->data = data;
}

void
_vglyph_data_surface_ctor(vglyph_data_surface_t* surface)
{
    _vglyph_surface_ctor(&surface->base);

    if (_vglyph_data_surface_is_valid(surface))
    {
    }
}

void
_vglyph_data_surface_dtor(vglyph_data_surface_t* surface)
{
    _vglyph_surface_dtor(&surface->base);
}

vglyph_bool_t
_vglyph_data_surface_is_cast(vglyph_type_t* type)
{
    return _vglyph_data_surface_get_type() == type
        || _vglyph_surface_is_cast(type);
}

vglyph_type_t*
_vglyph_data_surface_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_data_surface_is_cast);
    return &type;
}

static void
_vglyph_data_surface_destroy(vglyph_object_t* object)
{
    vglyph_data_surface_t* surface = (vglyph_data_surface_t*)object;
    _vglyph_data_surface_dtor(surface);

    free(surface);
}

vglyph_uint8_t*
_vglyph_data_surface_lock(vglyph_surface_t* surface,
                          vglyph_uint32_t x,
                          vglyph_uint32_t y,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height)
{
    return ((vglyph_data_surface_t*)surface)->data;
}

void
_vglyph_data_surface_unlock(vglyph_surface_t* surface)
{
}

static const vglyph_object_backend_t vglyph_data_surface_object_backend = {
    _vglyph_data_surface_get_type,
    _vglyph_data_surface_is_cast,
    _vglyph_data_surface_destroy
};

static const vglyph_surface_backend_t vglyph_data_surface_backend = {
    _vglyph_data_surface_lock,
    _vglyph_data_surface_unlock
};

vglyph_uint32_t
_vglyph_data_surface_get_pitch(vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_alignment_t row_alignment)
{
    assert(format);
    assert(row_alignment == VGLYPH_ALIGNMENT_1 ||
           row_alignment == VGLYPH_ALIGNMENT_2 ||
           row_alignment == VGLYPH_ALIGNMENT_4 ||
           row_alignment == VGLYPH_ALIGNMENT_8);

    vglyph_uint32_t bits_per_pixel = vglyph_format_get_bits_per_pixel(format);
    vglyph_uint32_t pitch = (width * bits_per_pixel + 7) >> 3;
    vglyph_uint32_t align = row_alignment - 1;
    pitch = (pitch + align) & ~align;

    return pitch;
}

vglyph_uint32_t
vglyph_surface_get_data_size(vglyph_format_t* format,
                             vglyph_uint32_t width,
                             vglyph_uint32_t height,
                             vglyph_alignment_t row_alignment)
{
    vglyph_uint32_t pitch =
        _vglyph_data_surface_get_pitch(format, width, height, row_alignment);

    return pitch * height;
}

vglyph_surface_t*
vglyph_surface_create_for_data(vglyph_uint8_t* data,
                               vglyph_uint32_t data_size,
                               vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_alignment_t row_alignment)
{
    assert(data);
    assert(format);
    assert(data_size >= vglyph_surface_get_data_size(format, width, height, row_alignment));

    vglyph_data_surface_t* surface = (vglyph_data_surface_t*)malloc(sizeof(vglyph_data_surface_t));

    if (!surface)
        return (vglyph_surface_t*)_vglyph_object_out_of_memory();

    vglyph_uint32_t pitch =
        _vglyph_data_surface_get_pitch(format, width, height, row_alignment);

    _vglyph_data_surface_init(surface,
                              &vglyph_data_surface_object_backend,
                              &vglyph_data_surface_backend, 
                              format,
                              width,
                              height,
                              pitch,
                              data);

    _vglyph_data_surface_ctor(surface);

    return &surface->base;
}
