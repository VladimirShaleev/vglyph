/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"

static vglyph_uuid_t _vglyph_surface_type = {
    0x018f0c8d, 0xb600, 0x4bcb, 0xb6, 0xce,{ 0xfc, 0xf6, 0x31, 0xfd, 0xfe, 0x2b }
};

void
_vglyph_surface_init(vglyph_surface_t* surface,
                     vglyph_object_is_cast_func_t is_cast_func,
                     vglyph_object_destroy_func_t destroy_func)
{
    _vglyph_object_init(&surface->object, is_cast_func, destroy_func);
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
    return _vglyph_uuid_equal(uuid, &_vglyph_surface_type);
}

static void
_vglyph_surface_destroy(vglyph_object_t* object)
{
    vglyph_surface_t* surface = (vglyph_surface_t*)object;
    _vglyph_surface_dtor(surface);

    free(surface);
}

vglyph_surface_t*
vglyph_surface_create(void)
{
    vglyph_surface_t* surface = (vglyph_surface_t*)malloc(sizeof(vglyph_surface_t));

    if (!surface)
        return (vglyph_surface_t*)_vglyph_object_out_of_memory();

    _vglyph_surface_init(surface,
                         _vglyph_surface_is_cast,
                         _vglyph_surface_destroy);
    
    _vglyph_surface_ctor(surface);
    return surface;
}

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
    return (vglyph_surface_t*)_vglyph_object_to_type(object, &_vglyph_surface_type);
}
