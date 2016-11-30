﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-figure.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-figure.h"

static void
_vglyph_figure_init(vglyph_figure_t* figure,
                    vglyph_object_is_cast_func_t is_cast_func,
                    vglyph_object_destroy_func_t destroy_func)
{
    _vglyph_object_init(&figure->object, is_cast_func, destroy_func);
}

static void
_vglyph_figure_ctor(vglyph_figure_t* figure)
{
}

static void
_vglyph_figure_dtor(vglyph_figure_t* figure)
{
}

static vglyph_bool_t
_vglyph_figure_is_cast(vglyph_object_t* object,
                       vglyph_type_t type)
{
    return type == VGLYPH_TYPE_FIGURE ? TRUE : FALSE;
}

static void
_vglyph_figure_destroy(vglyph_object_t* object)
{
    vglyph_figure_t* figure = (vglyph_figure_t*)object;
    _vglyph_figure_dtor(figure);

    free(figure);
}

vglyph_figure_t*
vglyph_figure_create(void)
{
    vglyph_figure_t* figure = (vglyph_figure_t*)malloc(sizeof(vglyph_figure_t));

    if (!figure)
        return (vglyph_figure_t*)_vglyph_object_out_of_memory();

    _vglyph_figure_init(figure,
                        _vglyph_figure_is_cast,
                        _vglyph_figure_destroy);
    
    _vglyph_figure_ctor(figure);
    return figure;
}

vglyph_figure_t*
vglyph_figure_reference(vglyph_figure_t* figure)
{
    assert(figure);
    return (vglyph_figure_t*)_vglyph_object_reference(&figure->object);
}

void
vglyph_figure_destroy(vglyph_figure_t* figure)
{
    assert(figure);
    _vglyph_object_destroy(&figure->object);
}

int
vglyph_figure_get_reference_count(vglyph_figure_t* figure)
{
    assert(figure);
    return _vglyph_object_get_reference_count(&figure->object);
}

vglyph_state_t
vglyph_figure_get_state(vglyph_figure_t* figure)
{
    assert(figure);
    return _vglyph_object_get_state(&figure->object);
}

vglyph_object_t*
vglyph_figure_figure_to_object(vglyph_figure_t* figure)
{
    assert(figure);
    return &figure->object;
}

vglyph_figure_t*
vglyph_figure_object_to_figure(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_figure_t*)vglyph_object_to_type(object, VGLYPH_TYPE_FIGURE);
}
