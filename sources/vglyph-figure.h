﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-figure.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_FIGURE_H
#define VGLYPH_FIGURE_H

#include "vglyph-object.h"
#include "vglyph-vector.h"
#include "vglyph-segment-types.h"

typedef struct _vglyph_segment_type
{
    vglyph_segment_t segment;
    vglyph_uint_t    offset;
} vglyph_segment_type_t;

struct _vglyph_figure
{
    vglyph_object_t  object;
    vglyph_uint_t    segment_count;
    vglyph_vector_t* segment_types;
    vglyph_vector_t* segments;
};

static inline void
_vglyph_figure_set_state(vglyph_figure_t* figure,
                         vglyph_state_t state)
{
    assert(figure);
    _vglyph_object_set_state(&figure->object, state);
}

static inline vglyph_bool_t
_vglyph_figure_is_valid(vglyph_figure_t* figure)
{
    assert(figure);
    return _vglyph_object_is_valid(&figure->object);
}

static inline vglyph_segment_type_t*
_vglyph_figure_add_segment_type(vglyph_figure_t* figure)
{
    assert(figure);

    ++figure->segment_count;

    vglyph_uint_t offset =
        _vglyph_vector_push(figure->segment_types, sizeof(vglyph_segment_type_t));

    if (!_vglyph_vector_is_valid(figure->segment_types))
    {
        _vglyph_figure_set_state(figure, _vglyph_vector_get_state(figure->segment_types));
        return NULL;
    }

    return (vglyph_segment_type_t*)_vglyph_vector_at(figure->segment_types, offset);
}

#define VGLYPH_RESULT_TYPE
#define _vglyph_figure_add_segment(_figure, _segment, _result)                               \
{                                                                                            \
    vglyph_segment_type_t* _segment_type = _vglyph_figure_add_segment_type(_figure);         \
                                                                                             \
    if (!_segment_type)                                                                      \
        _result = NULL;                                                                      \
                                                                                             \
    _segment_type->segment = _segment;                                                       \
    _segment_type->offset = _vglyph_vector_push(                                             \
        _figure->segments, sizeof(VGLYPH_RESULT_TYPE));                                      \
                                                                                             \
    if (!_vglyph_vector_is_valid(_figure->segments))                                         \
    {                                                                                        \
        _vglyph_figure_set_state(_figure, _vglyph_vector_get_state(_figure->segments));      \
        _result = NULL;                                                                      \
    }                                                                                        \
    else                                                                                     \
    {                                                                                        \
        _result = (VGLYPH_RESULT_TYPE*)                                                      \
            _vglyph_vector_at(_figure->segments, _segment_type->offset);                     \
    }                                                                                        \
}

#endif