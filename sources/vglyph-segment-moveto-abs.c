/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment-moveto-abs.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-segment-moveto-abs.h"

static void
_vglyph_segment_moveto_abs_init(vglyph_segment_moveto_abs_t* segment_moveto_abs,
                                vglyph_object_is_cast_func_t is_cast_func,
                                vglyph_object_destroy_func_t destroy_func,
                                const vglyph_point_t* point)
{
    _vglyph_segment_init(&segment_moveto_abs->base, is_cast_func, destroy_func);

    segment_moveto_abs->point = *point;
}

static void
_vglyph_segment_moveto_abs_ctor(vglyph_segment_moveto_abs_t* segment_moveto_abs)
{
    _vglyph_segment_ctor(&segment_moveto_abs->base);

    if (_vglyph_segment_moveto_abs_is_valid(segment_moveto_abs))
    {
    }
}

static void
_vglyph_segment_moveto_abs_dtor(vglyph_segment_moveto_abs_t* segment_moveto_abs)
{
    _vglyph_segment_dtor(&segment_moveto_abs->base);
}

static vglyph_bool_t
_vglyph_segment_moveto_abs_is_cast(vglyph_object_t* object,
                                   vglyph_type_t type)
{
    if (type == VGLYPH_TYPE_SEGMENT_MOVETO_ABS)
        return TRUE;

    return _vglyph_segment_is_cast(object, type);
}

static void
_vglyph_segment_moveto_abs_destroy(vglyph_object_t* object)
{
    vglyph_segment_moveto_abs_t* segment_moveto_abs = (vglyph_segment_moveto_abs_t*)object;
    _vglyph_segment_moveto_abs_dtor(segment_moveto_abs);

    free(segment_moveto_abs);
}

vglyph_segment_t*
vglyph_segment_moveto_abs_create(const vglyph_point_t* point)
{
    vglyph_segment_moveto_abs_t* segment_moveto_abs = 
        (vglyph_segment_moveto_abs_t*)malloc(sizeof(vglyph_segment_moveto_abs_t));

    if (!segment_moveto_abs)
        return (vglyph_segment_t*)_vglyph_object_out_of_memory();

    _vglyph_segment_moveto_abs_init(segment_moveto_abs,
                                    _vglyph_segment_moveto_abs_is_cast,
                                    _vglyph_segment_moveto_abs_destroy,
                                    point);

    _vglyph_segment_moveto_abs_ctor(segment_moveto_abs);
    return &segment_moveto_abs->base;
}
