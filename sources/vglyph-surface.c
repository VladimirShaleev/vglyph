/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"

static vglyph_uuid_t vglyph_surface_type = {
    0x018f0c8d, 0xb600, 0x4bcb, 0xb6, 0xce, { 0xfc, 0xf6, 0x31, 0xfd, 0xfe, 0x2b }
};

void
_vglyph_surface_init(vglyph_surface_t* surface,
                     const vglyph_object_backend_t* object_backend)
{
    _vglyph_object_init(&surface->object, object_backend);
}

void
_vglyph_surface_ctor(vglyph_surface_t* surface)
{
}

void
_vglyph_surface_dtor(vglyph_surface_t* surface)
{
}

vglyph_bool_t
_vglyph_surface_is_cast(vglyph_uuid_t* uuid)
{
    return _vglyph_uuid_equal(uuid, &vglyph_surface_type);
}

static void
_vglyph_surface_destroy(vglyph_object_t* object)
{
    vglyph_surface_t* surface = (vglyph_surface_t*)object;
    _vglyph_surface_dtor(surface);

    free(surface);
}

static const vglyph_object_backend_t vglyph_surface_object_backend = {
    _vglyph_surface_is_cast,
    _vglyph_surface_destroy
};

vglyph_object_t*
vglyph_surface_to_object(vglyph_surface_t* surface)
{
    assert(surface);
    return &surface->object;
}

vglyph_surface_t*
vglyph_object_to_surface(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_surface_t*)_vglyph_object_to_type(object, &vglyph_surface_type);
}
