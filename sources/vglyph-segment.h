/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_SEGMENT_H
#define VGLYPH_SEGMENT_H

#include "vglyph-object.h"

struct _vglyph_segment
{
    vglyph_object_t object;
    vglyph_segment_type_t type;
};

static inline void
_vglyph_segment_init(vglyph_segment_t* segment,
                     vglyph_object_is_cast_func_t is_cast_func,
                     vglyph_object_destroy_func_t destroy_func)
{
    _vglyph_object_init(&segment->object, is_cast_func, destroy_func);
}

static inline void
_vglyph_segment_ctor(vglyph_segment_t* segment)
{
}

static inline void
_vglyph_segment_dtor(vglyph_segment_t* segment)
{
}

static inline void
_vglyph_segment_set_state(vglyph_segment_t* segment,
                          vglyph_state_t state)
{
    assert(segment);
    _vglyph_object_set_state(&segment->object, state);
}

static inline vglyph_bool_t
_vglyph_segment_is_valid(vglyph_segment_t* segment)
{
    assert(segment);
    return _vglyph_object_is_valid(&segment->object);
}

static inline vglyph_bool_t
_vglyph_segment_is_cast(vglyph_object_t* object,
                        vglyph_type_t type)
{
    return type == VGLYPH_TYPE_SEGMENT ? TRUE : FALSE;
}

#endif
