﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-figure.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_FIGURE_H
#define VGLYPH_FIGURE_H

#include "vglyph-object.h"
#include "vglyph-vector.h"
#include "vglyph-rectangle.h"
#include "vglyph-segment-types.h"

typedef struct _vglyph_segment_type
{
    vglyph_segment_t segment;
    vglyph_uint_t    offset;
} vglyph_segment_type_t;

struct _vglyph_figure
{
    vglyph_object_t    object;
    vglyph_uint_t      segment_count;
    vglyph_vector_t*   segment_types;
    vglyph_vector_t*   segments;
    vglyph_uint_t      compute_bound_offset;
    vglyph_rectangle_t bound;
};

vglyph_point_t*
_vglyph_figure_cubic_bezier(vglyph_point_t* result,
                            const vglyph_point_t* point0,
                            const vglyph_point_t* point1,
                            const vglyph_point_t* point2,
                            const vglyph_point_t* point3,
                            vglyph_float32_t t);

vglyph_point_t*
_vglyph_figure_quadratic_bezier(vglyph_point_t* result,
                                const vglyph_point_t* point0,
                                const vglyph_point_t* point1,
                                const vglyph_point_t* point2,
                                vglyph_float32_t t);

vglyph_bool_t
_vglyph_figure_get_arc_params(vglyph_point_t* result_radius,
                              vglyph_point_t* result_center,
                              vglyph_float32_t* result_cos_fi,
                              vglyph_float32_t* result_sin_fi,
                              vglyph_float32_t* result_theta_0,
                              vglyph_float32_t* result_theta_d,
                              const vglyph_point_t* point0,
                              const vglyph_point_t* point1,
                              const vglyph_point_t* radius,
                              vglyph_float32_t fi,
                              vglyph_bool_t f_a,
                              vglyph_bool_t f_s);

vglyph_point_t*
_vglyph_figure_arc(vglyph_point_t* result,
                   const vglyph_point_t* radius,
                   const vglyph_point_t* center,
                   vglyph_float32_t cos_fi,
                   vglyph_float32_t sin_fi,
                   vglyph_float32_t theta);

vglyph_float32_t
_vglyph_figure_get_cubic_bezier_length(const vglyph_point_t* point0,
                                       const vglyph_point_t* point1,
                                       const vglyph_point_t* point2,
                                       const vglyph_point_t* point3);

vglyph_float32_t
_vglyph_figure_get_quadratic_bezier_length(const vglyph_point_t* point0,
                                           const vglyph_point_t* point1,
                                           const vglyph_point_t* point2);

vglyph_float32_t
_vglyph_figure_get_arc_length(const vglyph_point_t* radius,
                              const vglyph_point_t* center,
                              vglyph_float32_t cos_fi,
                              vglyph_float32_t sin_fi,
                              vglyph_float32_t theta_0,
                              vglyph_float32_t theta_d);

vglyph_rectangle_t*
_vglyph_figure_get_line_rectangle(vglyph_rectangle_t* rectangle,
                                  const vglyph_point_t* point0,
                                  const vglyph_point_t* point1);

vglyph_rectangle_t*
_vglyph_figure_get_cubic_bezier_rectangle(vglyph_rectangle_t* rectangle,
                                          const vglyph_point_t* point0,
                                          const vglyph_point_t* point1,
                                          const vglyph_point_t* point2,
                                          const vglyph_point_t* point3);

vglyph_rectangle_t*
_vglyph_figure_get_quadratic_bezier_rectangle(vglyph_rectangle_t* rectangle,
                                              const vglyph_point_t* point0,
                                              const vglyph_point_t* point1,
                                              const vglyph_point_t* point2);

vglyph_rectangle_t*
_vglyph_figure_get_arc_rectangle(vglyph_rectangle_t* rectangle,
                                 const vglyph_point_t* radius,
                                 const vglyph_point_t* center,
                                 vglyph_float32_t cos_fi,
                                 vglyph_float32_t sin_fi,
                                 vglyph_float32_t theta_0,
                                 vglyph_float32_t theta_d);

vglyph_rectangle_t*
_vglyph_figure_get_bound(vglyph_figure_t* figure,
                         vglyph_rectangle_t* result);

static inline vglyph_figure_t*
_vglyph_figure_reference(vglyph_figure_t* figure)
{
    assert(figure);
    return (vglyph_figure_t*)_vglyph_object_reference(&figure->object);
}

static inline void
_vglyph_figure_destroy(vglyph_figure_t* figure)
{
    assert(figure);
    _vglyph_object_destroy(&figure->object);
}

static inline int
_vglyph_figure_get_reference_count(vglyph_figure_t* figure)
{
    assert(figure);
    return _vglyph_object_get_reference_count(&figure->object);
}

static inline vglyph_state_t
_vglyph_figure_get_state(vglyph_figure_t* figure)
{
    assert(figure);
    return _vglyph_object_get_state(&figure->object);
}

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
        _vglyph_object_set_state_not_fatal(&figure->object);

        vglyph_object_reset_state(&figure->segment_types->object);
        return NULL;
    }

    return (vglyph_segment_type_t*)_vglyph_vector_at(figure->segment_types, offset);
}

#define VGLYPH_RESULT_TYPE
#define _vglyph_figure_add_segment(_figure, _segment, _result)                                   \
{                                                                                                \
    vglyph_segment_type_t* _segment_type = _vglyph_figure_add_segment_type(_figure);             \
                                                                                                 \
    if (!_segment_type)                                                                          \
        _result = NULL;                                                                          \
                                                                                                 \
    _segment_type->segment = _segment;                                                           \
    _segment_type->offset = _vglyph_vector_push(_figure->segments, sizeof(VGLYPH_RESULT_TYPE));  \
                                                                                                 \
    if (!_vglyph_vector_is_valid(_figure->segments))                                             \
    {                                                                                            \
        _vglyph_figure_set_state(_figure, _vglyph_vector_get_state(_figure->segments));          \
        _vglyph_object_set_state_not_fatal(&figure->object);                                     \
                                                                                                 \
        vglyph_object_reset_state(&_figure->segments->object);                                   \
        _result = NULL;                                                                          \
    }                                                                                            \
    else                                                                                         \
    {                                                                                            \
        _result = (VGLYPH_RESULT_TYPE*)                                                          \
            _vglyph_vector_at(_figure->segments, _segment_type->offset);                         \
    }                                                                                            \
}

#endif
