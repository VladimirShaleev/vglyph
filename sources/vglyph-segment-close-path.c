/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment-close-path.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-segment-close-path.h"

static void
_vglyph_segment_close_path_init(vglyph_segment_close_path_t* segment_close_path,
                                vglyph_object_is_cast_func_t is_cast_func,
                                vglyph_object_destroy_func_t destroy_func)
{
    _vglyph_segment_init(&segment_close_path->base, is_cast_func, destroy_func);
}

static void
_vglyph_segment_close_path_ctor(vglyph_segment_close_path_t* segment_close_path)
{
    _vglyph_segment_ctor(&segment_close_path->base);

    if (_vglyph_segment_close_path_is_valid(segment_close_path))
    {
    }
}

static void
_vglyph_segment_close_path_dtor(vglyph_segment_close_path_t* segment_close_path)
{
    _vglyph_segment_dtor(&segment_close_path->base);
}

static vglyph_bool_t
_vglyph_segment_close_path_is_cast(vglyph_object_t* object,
                                   vglyph_type_t type)
{
    if (type == VGLYPH_TYPE_SEGMENT_CLOSE_PATH)
        return TRUE;

    return _vglyph_segment_is_cast(object, type);
}

static void
_vglyph_segment_close_path_destroy(vglyph_object_t* object)
{
    vglyph_segment_close_path_t* segment_close_path = (vglyph_segment_close_path_t*)object;
    _vglyph_segment_close_path_dtor(segment_close_path);

    free(segment_close_path);
}

vglyph_segment_t*
vglyph_segment_close_path_create(void)
{
    vglyph_segment_close_path_t* segment_close_path = 
        (vglyph_segment_close_path_t*)malloc(sizeof(vglyph_segment_close_path_t));

    if (!segment_close_path)
        return (vglyph_segment_t*)_vglyph_object_out_of_memory();

    _vglyph_segment_close_path_init(segment_close_path,
                                    _vglyph_segment_close_path_is_cast,
                                    _vglyph_segment_close_path_destroy);

    _vglyph_segment_close_path_ctor(segment_close_path);
    return &segment_close_path->base;
}
