/* vglyph - library for visualize glyphs
 *
 * File: vglyph-data-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-data-surface.h"

static vglyph_uuid_t vglyph_data_surface_type = {
    0x00714ba3, 0xa35f, 0x43c2, 0x9b, 0x6a, { 0x69, 0x40, 0x70, 0x42, 0x11, 0x34 }
};

void
_vglyph_data_surface_init(vglyph_data_surface_t* surface,
                          const vglyph_object_backend_t* object_backend)
{
    _vglyph_surface_init(&surface->base, object_backend);
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
_vglyph_data_surface_is_cast(vglyph_uuid_t* uuid)
{
    return _vglyph_uuid_equal(uuid, &vglyph_data_surface_type)
        || _vglyph_surface_is_cast(uuid);
}

static void
_vglyph_data_surface_destroy(vglyph_object_t* object)
{
    vglyph_data_surface_t* surface = (vglyph_data_surface_t*)object;
    _vglyph_data_surface_dtor(surface);

    free(surface);
}

static const vglyph_object_backend_t vglyph_data_surface_object_backend = {
    _vglyph_data_surface_is_cast,
    _vglyph_data_surface_destroy
};

vglyph_surface_t*
vglyph_surface_create_for_data(unsigned char* data,
                               const vglyph_format_t* format,
                               unsigned int width,
                               unsigned int height)
{
    assert(data);
    assert(format);

    vglyph_data_surface_t* surface = (vglyph_data_surface_t*)malloc(sizeof(vglyph_data_surface_t));

    if (!surface)
        return (vglyph_surface_t*)_vglyph_object_out_of_memory();

    _vglyph_data_surface_init(surface, &vglyph_data_surface_object_backend);
    _vglyph_data_surface_ctor(surface);

    return &surface->base;
}
