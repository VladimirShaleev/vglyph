/* vglyph - library for visualize glyphs
 *
 * File: vglyph-figure.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-figure.h"
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
