﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"

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

static vglyph_bool_t
_vglyph_surface_is_cast_callback(vglyph_object_t* object,
                                 vglyph_type_t type)
{
    return _vglyph_surface_is_cast(object, type);
}

static void
_vglyph_surface_destroy_callback(vglyph_object_t* object)
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
                        _vglyph_surface_is_cast_callback,
                        _vglyph_surface_destroy_callback);
    
    _vglyph_surface_ctor(surface);
    return surface;
}

vglyph_surface_t*
vglyph_surface_reference(vglyph_surface_t* surface)
{
    assert(surface);
    return (vglyph_surface_t*)_vglyph_object_reference(&surface->object);
}

void
vglyph_surface_destroy(vglyph_surface_t* surface)
{
    assert(surface);
    _vglyph_object_destroy(&surface->object);
}

int
vglyph_surface_get_reference_count(vglyph_surface_t* surface)
{
    assert(surface);
    return _vglyph_object_get_reference_count(&surface->object);
}

vglyph_state_t
vglyph_surface_get_state(vglyph_surface_t* surface)
{
    assert(surface);
    return _vglyph_object_get_state(&surface->object);
}

vglyph_object_t*
vglyph_surface_surface_to_object(vglyph_surface_t* surface)
{
    assert(surface);
    return _vglyph_object_reference(&surface->object);
}

vglyph_surface_t*
vglyph_surface_object_to_surface(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_surface_t*)_vglyph_object_to_type(object, VGLYPH_TYPE_FIGURE);
}
