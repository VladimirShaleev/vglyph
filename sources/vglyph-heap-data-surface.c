/* vglyph - library for visualize glyphs
 *
 * File: vglyph-heap-data-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-heap-data-surface.h"
#include "vglyph-type.h"

void
_vglyph_heap_data_surface_init(vglyph_heap_data_surface_t* surface,
                               const vglyph_object_backend_t* object_backend,
                               const vglyph_surface_backend_t* surface_backend,
                               vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_uint32_t pitch,
                               vglyph_uint8_t* data)
{
    _vglyph_data_surface_init(&surface->base,
                              object_backend,
                              surface_backend,
                              format,
                              width,
                              height,
                              pitch,
                              data);
}

void
_vglyph_heap_data_surface_ctor(vglyph_heap_data_surface_t* surface)
{
    _vglyph_data_surface_ctor(&surface->base);

    if (_vglyph_heap_data_surface_is_valid(surface))
    {
    }
}

void
_vglyph_heap_data_surface_dtor(vglyph_heap_data_surface_t* surface)
{
    free(surface->base.data);

    _vglyph_data_surface_dtor(&surface->base);
}

vglyph_bool_t
_vglyph_heap_data_surface_is_cast(vglyph_type_t* type)
{
    return _vglyph_heap_data_surface_get_type() == type
        || _vglyph_data_surface_is_cast(type);
}

vglyph_type_t*
_vglyph_heap_data_surface_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_heap_data_surface_is_cast);
    return &type;
}

static void
_vglyph_heap_data_surface_destroy(vglyph_object_t* object)
{
    vglyph_heap_data_surface_t* surface = (vglyph_heap_data_surface_t*)object;
    _vglyph_heap_data_surface_dtor(surface);

    free(surface);
}

vglyph_uint8_t*
_vglyph_heap_data_surface_lock(vglyph_surface_t* surface,
                               vglyph_uint32_t x,
                               vglyph_uint32_t y,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height)
{
    return _vglyph_data_surface_lock(surface, x, y, width, height);
}

void
_vglyph_heap_data_surface_unlock(vglyph_surface_t* surface)
{
    _vglyph_data_surface_unlock(surface);
}

static const vglyph_object_backend_t vglyph_heap_data_surface_object_backend = {
    _vglyph_heap_data_surface_get_type,
    _vglyph_heap_data_surface_is_cast,
    _vglyph_heap_data_surface_destroy
};

static const vglyph_surface_backend_t vglyph_heap_data_surface_backend = {
    _vglyph_heap_data_surface_lock,
    _vglyph_heap_data_surface_unlock
};

vglyph_surface_t*
vglyph_surface_create(vglyph_format_t* format,
                      vglyph_uint32_t width,
                      vglyph_uint32_t height,
                      vglyph_alignment_t row_alignment)
{
    assert(format);

    vglyph_uint32_t pitch     = _vglyph_data_surface_get_pitch(format, width, height, row_alignment);
    vglyph_uint32_t data_size = pitch * height;
    vglyph_uint8_t* data      = (vglyph_uint8_t*)malloc((size_t)data_size);

    if (!data)
        return (vglyph_surface_t*)_vglyph_object_out_of_memory();

    vglyph_heap_data_surface_t* surface = (vglyph_heap_data_surface_t*)malloc(sizeof(vglyph_heap_data_surface_t));

    if (!surface)
    {
        free(data);
        return (vglyph_surface_t*)_vglyph_object_out_of_memory();
    }

    _vglyph_heap_data_surface_init(surface,
                                   &vglyph_heap_data_surface_object_backend,
                                   &vglyph_heap_data_surface_backend,
                                   format,
                                   width,
                                   height,
                                   pitch,
                                   data);

    _vglyph_heap_data_surface_ctor(surface);

    return &surface->base.base;
}
