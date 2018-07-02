﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-figure.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-figure.h"
#include "vglyph-point.h"
#include "vglyph-type.h"

static void
_vglyph_figure_init(vglyph_figure_t* figure,
                    const vglyph_object_backend_t* object_backend)
{
    _vglyph_object_init(&figure->object, object_backend);

    figure->segment_count = 0;
    figure->segment_types = NULL;
    figure->segments      = NULL;
}

static void
_vglyph_figure_ctor(vglyph_figure_t* figure)
{
    figure->segment_types = _vglyph_vector_create(sizeof(vglyph_segment_type_t) * 8);
    figure->segments      = _vglyph_vector_create(sizeof(vglyph_float32_t) * 8);

    if (!_vglyph_vector_is_valid(figure->segment_types))
    {
        _vglyph_figure_set_state(figure, _vglyph_vector_get_state(figure->segment_types));
        return;
    }

    if (!_vglyph_vector_is_valid(figure->segments))
    {
        _vglyph_figure_set_state(figure, _vglyph_vector_get_state(figure->segments));
        return;
    }
}

static void
_vglyph_figure_dtor(vglyph_figure_t* figure)
{
    if (figure->segment_types)
    {
        _vglyph_vector_destroy(figure->segment_types);
        figure->segment_types = NULL;
    }

    if (figure->segments)
    {
        _vglyph_vector_destroy(figure->segments);
        figure->segments = NULL;
    }
}

static vglyph_bool_t
_vglyph_figure_is_cast(vglyph_type_t* type)
{
    return vglyph_get_figure_type() == type;
}

static void
_vglyph_figure_destroy_callback(vglyph_object_t* object)
{
    vglyph_figure_t* figure = (vglyph_figure_t*)object;
    _vglyph_figure_dtor(figure);

    free(figure);
}

static vglyph_bool_t
_vglyph_figure_cubic_bezier_min_max_t(vglyph_float32_t* t1,
                                      vglyph_float32_t* t2,
                                      vglyph_float32_t x0,
                                      vglyph_float32_t x1,
                                      vglyph_float32_t x2,
                                      vglyph_float32_t x3)
{
    vglyph_float32_t a = 3.0f * (x3 - x0 + 3.0f * (x1 - x2));
    vglyph_float32_t b = 6.0f * (x0 - 2.0f * x1 + x2);
    vglyph_float32_t c = 3.0f * (x1 - x0);

    vglyph_float32_t D = b * b - 4.0f * a * c;

    if (D >= 0.0f)
    {
        vglyph_float32_t sqrtD = sqrtf(D);
        vglyph_float32_t invDiv = 1.0f / (2.0f * a);

        *t1 = (-b + sqrtD) * invDiv;
        *t2 = (-b - sqrtD) * invDiv;

        return TRUE;
    }

    return FALSE;
}

vglyph_point_t*
_vglyph_figure_cubic_bezier(vglyph_point_t* result,
                            const vglyph_point_t* point0,
                            const vglyph_point_t* point1,
                            const vglyph_point_t* point2,
                            const vglyph_point_t* point3,
                            vglyph_float32_t t)
{
    assert(result);
    assert(point0);
    assert(point1);
    assert(point2);
    assert(point3);

    vglyph_float32_t t_pow_1 = t;
    vglyph_float32_t t_pow_2 = t_pow_1 * t_pow_1;
    vglyph_float32_t t_pow_3 = t_pow_2 * t_pow_1;

    vglyph_float32_t inv_t_pow_1 = 1.0f - t;
    vglyph_float32_t inv_t_pow_2 = inv_t_pow_1 * inv_t_pow_1;
    vglyph_float32_t inv_t_pow_3 = inv_t_pow_2 * inv_t_pow_1;

    vglyph_point_t p0;
    vglyph_point_t p1;
    vglyph_point_t p2;
    vglyph_point_t p3;

    _vglyph_point_mul(&p0, point0,                  inv_t_pow_3);
    _vglyph_point_mul(&p1, point1, 3.0f * t_pow_1 * inv_t_pow_2);
    _vglyph_point_mul(&p2, point2, 3.0f * t_pow_2 * inv_t_pow_1);
    _vglyph_point_mul(&p3, point3,         t_pow_3);

    _vglyph_point_add(result, &p0,    &p1);
    _vglyph_point_add(result, result, &p2);
    _vglyph_point_add(result, result, &p3);

    return result;
}

vglyph_rectangle_t*
_vglyph_figure_cubic_bezier_rectangle(vglyph_rectangle_t* rectangle,
                                      const vglyph_point_t* point0,
                                      const vglyph_point_t* point1,
                                      const vglyph_point_t* point2,
                                      const vglyph_point_t* point3)
{
    assert(rectangle);
    assert(point0);
    assert(point1);
    assert(point2);
    assert(point3);

    vglyph_float32_t t1;
    vglyph_float32_t t2;

    _vglyph_rectangle_init_from_points(rectangle, point0, point3);

    if (_vglyph_figure_cubic_bezier_min_max_t(&t1, &t2, point0->x, point1->x, point2->x, point3->x))
    {
        vglyph_point_t point;

        if (t1 >= 0.0f && t1 <= 1.0f)
        {
            _vglyph_figure_cubic_bezier(&point, point0, point1, point2, point3, t1);
            _vglyph_rectangle_add_point(rectangle, rectangle, &point);
        }

        if (t2 >= 0.0f && t2 <= 1.0f)
        {
            _vglyph_figure_cubic_bezier(&point, point0, point1, point2, point3, t2);
            _vglyph_rectangle_add_point(rectangle, rectangle, &point);
        }
    }

    if (_vglyph_figure_cubic_bezier_min_max_t(&t1, &t2, point0->y, point1->y, point2->y, point3->y))
    {
        vglyph_point_t point;

        if (t1 >= 0.0f && t1 <= 1.0f)
        {
            _vglyph_figure_cubic_bezier(&point, point0, point1, point2, point3, t1);
            _vglyph_rectangle_add_point(rectangle, rectangle, &point);
        }

        if (t2 >= 0.0f && t2 <= 1.0f)
        {
            _vglyph_figure_cubic_bezier(&point, point0, point1, point2, point3, t2);
            _vglyph_rectangle_add_point(rectangle, rectangle, &point);
        }
    }

    return rectangle;
}

static const vglyph_object_backend_t vglyph_figure_object_backend = {
    vglyph_get_figure_type,
    _vglyph_figure_is_cast,
    _vglyph_figure_destroy_callback
};

vglyph_type_t*
vglyph_get_figure_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_figure_is_cast);
    return &type;
}

vglyph_figure_t*
vglyph_object_to_figure(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_figure_t*)_vglyph_object_to_type(object, vglyph_get_figure_type());
}

vglyph_figure_t*
vglyph_figure_create(void)
{
    vglyph_figure_t* figure = (vglyph_figure_t*)malloc(sizeof(vglyph_figure_t));

    if (!figure)
        return (vglyph_figure_t*)_vglyph_object_out_of_memory();

    _vglyph_figure_init(figure, &vglyph_figure_object_backend);
    _vglyph_figure_ctor(figure);

    return figure;
}

vglyph_object_t*
vglyph_figure_to_object(vglyph_figure_t* figure)
{
    assert(figure);
    return &figure->object;
}

vglyph_bool_t
vglyph_figure_draw_clear(vglyph_figure_t* figure)
{
    assert(figure);

    if (_vglyph_figure_is_valid(figure))
    {
        _vglyph_vector_clear(figure->segment_types);
        _vglyph_vector_clear(figure->segments);

        figure->segment_count = 0;

        return _vglyph_vector_is_valid(figure->segment_types) &&
               _vglyph_vector_is_valid(figure->segments);
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_closepath(vglyph_figure_t* figure)
{
    assert(figure);
    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_moveto(vglyph_figure_t* figure,
                          vglyph_coordinate_t coordinate,
                          const vglyph_point_t* point)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);
    assert(point);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_moveto_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_MOVETO_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->point = *point;
        return TRUE;
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_lineto(vglyph_figure_t* figure,
                          vglyph_coordinate_t coordinate,
                          const vglyph_point_t* point)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);
    assert(point);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_lineto_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_LINETO_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->point = *point;
        return TRUE;
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_curveto_cubic(vglyph_figure_t* figure,
                                 vglyph_coordinate_t coordinate,
                                 const vglyph_point_t* point,
                                 const vglyph_point_t* point1,
                                 const vglyph_point_t* point2)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);
    assert(point);
    assert(point1);
    assert(point2);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_curveto_cubic_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_CURVETO_CUBIC_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->point  = *point;
        result->point1 = *point1;
        result->point2 = *point2;
        return TRUE;
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_curveto_quadratic(vglyph_figure_t* figure,
                                     vglyph_coordinate_t coordinate,
                                     const vglyph_point_t* point,
                                     const vglyph_point_t* point1)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);
    assert(point);
    assert(point1);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_curveto_quadratic_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->point  = *point;
        result->point1 = *point1;
        return TRUE;
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_arc(vglyph_figure_t* figure,
                       vglyph_coordinate_t coordinate,
                       const vglyph_point_t* point,
                       const vglyph_point_t* radius,
                       vglyph_float32_t angle,
                       vglyph_bool_t large_arc_flag,
                       vglyph_bool_t sweep_flag)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);
    assert(point);
    assert(radius);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_arc_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_ARC_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->point          = *point;
        result->radius         = *radius;
        result->angle          = angle;
        result->large_arc_flag = large_arc_flag;
        result->sweep_flag     = sweep_flag;
        return TRUE;
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_lineto_horizontal(vglyph_figure_t* figure,
                                     vglyph_coordinate_t coordinate,
                                     vglyph_float32_t x)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_lineto_horizontal_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->x = x;
        return TRUE;
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_lineto_vertical(vglyph_figure_t* figure,
                                   vglyph_coordinate_t coordinate,
                                   vglyph_float32_t y)
{
    assert(figure);
    assert(coordinate == VGLYPH_COORDINATE_ABSOLUTE || coordinate == VGLYPH_COORDINATE_RELATIVE);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_lineto_vertical_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)(VGLYPH_SEGMENT_LINETO_VERTICAL_ABS + coordinate), result);

        if (!result)
            return FALSE;

        result->y = y;
        return TRUE;
    }

    return FALSE;
}
