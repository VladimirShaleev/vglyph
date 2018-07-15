/* vglyph - library for visualize glyphs
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

    figure->segment_count        = 0;
    figure->segment_types        = NULL;
    figure->segments             = NULL;
    figure->compute_bound_offset = 0;
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

static vglyph_point_t*
_vglyph_figure_offset_point(vglyph_point_t* result,
                            const vglyph_point_t* prev_point,
                            const vglyph_point_t* point,
                            vglyph_bool_t relative)
{
    assert(result);
    assert(prev_point);
    assert(point);
    
    *result = *point;

    if (relative)
    {
        result->x += prev_point->x;
        result->y += prev_point->y;
    }

    return result;
}

static void
_vglyph_figure_bound_union(vglyph_figure_t* figure,
                           const vglyph_rectangle_t* bound)
{
    assert(figure);
    assert(bound);

    if (figure->bound.left   != 0.0f ||
        figure->bound.top    != 0.0f ||
        figure->bound.right  != 0.0f ||
        figure->bound.bottom != 0.0f)
        _vglyph_rectangle_union(&figure->bound, &figure->bound, bound);
    else
        figure->bound = *bound;
}

static void
_vglyph_figure_arc_point_to_bezier(vglyph_point_t* result_point1,
                                   vglyph_point_t* result_point2,
                                   const vglyph_point_t* point0,
                                   const vglyph_point_t* point1,
                                   const vglyph_point_t* point2,
                                   const vglyph_point_t* point3)
{
    assert(result_point1);
    assert(result_point2);
    assert(point0);
    assert(point1);
    assert(point2);
    assert(point3);

    vglyph_point_t result1;
    vglyph_point_t result2;

    result1.x = (-5.0f * point0->x + 18.0f * point1->x -  9.0f * point2->x + 2.0f * point3->x) / 6.0f;
    result1.y = (-5.0f * point0->y + 18.0f * point1->y -  9.0f * point2->y + 2.0f * point3->y) / 6.0f;
    result2.x = ( 2.0f * point0->x -  9.0f * point1->x + 18.0f * point2->x - 5.0f * point3->x) / 6.0f;
    result2.y = ( 2.0f * point0->y -  9.0f * point1->y + 18.0f * point2->y - 5.0f * point3->y) / 6.0f;

    *result_point1 = result1;
    *result_point2 = result2;
}

static void
_vglyph_figure_get_arc_length_and_rect(vglyph_float32_t* length,
                                       vglyph_rectangle_t* rectangle,
                                       const vglyph_point_t* radius,
                                       const vglyph_point_t* center,
                                       vglyph_float32_t cos_fi,
                                       vglyph_float32_t sin_fi,
                                       vglyph_float32_t theta_0,
                                       vglyph_float32_t theta_d)
{
    assert(radius);
    assert(center);
    assert(radius->x != 0.0f);
    assert(radius->y != 0.0f);

    if (length)
        *length = 0.0f;

    const vglyph_sint_t part_count = 8;

    const vglyph_float32_t d             = theta_d / part_count;
    const vglyph_float32_t d_div_3       = d / 3.0f;
    const vglyph_float32_t d_div_3_mul_2 = d_div_3 * 2.0f;

    vglyph_float32_t theta_start;
    vglyph_float32_t theta1;
    vglyph_float32_t theta2;
    vglyph_float32_t theta3;

    vglyph_point_t point0;
    vglyph_point_t point1;
    vglyph_point_t point2;
    vglyph_point_t point3;

    vglyph_rectangle_t bound;

    _vglyph_figure_arc(&point0, radius, center, cos_fi, sin_fi, theta_0);

    for (vglyph_sint_t part = 0; part < part_count; ++part)
    {
        theta_start = theta_0 + d * (vglyph_float32_t)part;

        theta1 = theta_start + d_div_3;
        theta2 = theta_start + d_div_3_mul_2;
        theta3 = theta_start + d;

        _vglyph_figure_arc(&point1, radius, center, cos_fi, sin_fi, theta1);
        _vglyph_figure_arc(&point2, radius, center, cos_fi, sin_fi, theta2);
        _vglyph_figure_arc(&point3, radius, center, cos_fi, sin_fi, theta3);

        _vglyph_figure_arc_point_to_bezier(&point1, 
                                           &point2, 
                                           &point0, 
                                           &point1, 
                                           &point2, 
                                           &point3);

        if (length)
            *length += _vglyph_figure_get_cubic_bezier_length(&point0, &point1, &point2, &point3);

        if (rectangle)
        {
            _vglyph_figure_get_cubic_bezier_rectangle(&bound, &point0, &point1, &point2, &point3);

            if (part == 0)
                *rectangle = bound;
            else
                _vglyph_rectangle_union(rectangle, rectangle, &bound);
        }

        point0 = point3;
    }
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
                              vglyph_bool_t f_s)
{
    assert(point0);
    assert(point1);
    assert(radius);

    if (radius->x == 0.0f || radius->y == 0.0f)
        return FALSE;

    f_a = f_a ? 1 : 0;
    f_s = f_s ? 1 : 0;

    vglyph_float32_t radius_x = radius->x;
    vglyph_float32_t radius_y = radius->y;

    if (radius_x < 0.0f)
        radius_x = -radius_x;

    if (radius_y < 0.0f)
        radius_y = -radius_y;

    vglyph_float32_t radius_x_pow_2 = radius_x * radius_x;
    vglyph_float32_t radius_y_pow_2 = radius_y * radius_y;

    const vglyph_float32_t cos_fi = cosf(fi);
    const vglyph_float32_t sin_fi = sinf(fi);

    vglyph_point_t v;
    _vglyph_point_sub(&v, point0, point1);
    _vglyph_point_mul(&v, &v, 0.5f);

    const vglyph_float32_t p_x = cos_fi * v.x + sin_fi * v.y;
    const vglyph_float32_t p_y = cos_fi * v.y - sin_fi * v.x;

    const vglyph_float32_t p_x_pow_2 = p_x * p_x;
    const vglyph_float32_t p_y_pow_2 = p_y * p_y;

    const vglyph_float32_t lambda = 
        p_x_pow_2 / radius_x_pow_2 + 
        p_y_pow_2 / radius_y_pow_2;

    if (lambda > 1.0f)
    {
        const vglyph_float32_t lambda_sqrt = sqrtf(lambda);
        radius_x *= lambda_sqrt;
        radius_y *= lambda_sqrt;

        radius_x_pow_2 = radius_x * radius_x;
        radius_y_pow_2 = radius_y * radius_y;
    }

    const vglyph_float32_t rxpy = radius_x_pow_2 * p_y_pow_2;
    const vglyph_float32_t rypx = radius_y_pow_2 * p_x_pow_2;

    vglyph_float32_t k =
        sqrtf((radius_x_pow_2 * radius_y_pow_2 - rxpy - rypx) / (rxpy + rypx));

    if (f_a == f_s)
        k = -k;

    vglyph_float32_t p_c_x =  k * radius_x * p_y / radius_y;
    vglyph_float32_t p_c_y = -k * radius_y * p_x / radius_x;

    _vglyph_point_add(&v, point0, point1);
    _vglyph_point_mul(&v, &v, 0.5f);

    const vglyph_float32_t c_x = cos_fi * p_c_x - sin_fi * p_c_y + v.x;
    const vglyph_float32_t c_y = sin_fi * p_c_x + cos_fi * p_c_y + v.y;

    const vglyph_float32_t theta_0_x = (p_x - p_c_x) / radius_x;
    const vglyph_float32_t theta_0_y = (p_y - p_c_y) / radius_y;

    const vglyph_float32_t theta_d_x = -(p_x + p_c_x) / radius_x;
    const vglyph_float32_t theta_d_y = -(p_y + p_c_y) / radius_y;

    vglyph_float32_t theta_0 = atan2f(1.0f, 0.0f) - atan2f(theta_0_x, theta_0_y);
    vglyph_float32_t theta_d = atan2f(theta_0_x, theta_0_y) - atan2f(theta_d_x, theta_d_y);

    const vglyph_float32_t pi = 3.14159265358979323846f;

    if (!f_s && theta_d > 0.0f)
        theta_d -= pi * 2.0f;
    else if (f_s && theta_d < 0.0f)
        theta_d += pi * 2.0f;

    if (result_radius)
    {
        result_radius->x = radius_x;
        result_radius->y = radius_y;
    }
    
    if (result_center)
    {
        result_center->x = c_x;
        result_center->y = c_y;
    }
    
    if (result_cos_fi)
        *result_cos_fi = cos_fi;

    if (result_sin_fi)
        *result_sin_fi = sin_fi;

    if (result_theta_0)
        *result_theta_0 = theta_0;
    
    if (result_theta_d)
        *result_theta_d = theta_d;

    return TRUE;
}

vglyph_point_t*
_vglyph_figure_arc(vglyph_point_t* result,
                   const vglyph_point_t* radius,
                   const vglyph_point_t* center,
                   vglyph_float32_t cos_fi,
                   vglyph_float32_t sin_fi,
                   vglyph_float32_t theta)
{
    assert(result);
    assert(radius);
    assert(center);

    const vglyph_float32_t radius_x_cos_theta = radius->x * cosf(theta);
    const vglyph_float32_t radius_y_sin_theta = radius->y * sinf(theta);

    result->x = cos_fi * radius_x_cos_theta - sin_fi * radius_y_sin_theta + center->x;
    result->y = sin_fi * radius_x_cos_theta + cos_fi * radius_y_sin_theta + center->y;

    return result;
}

vglyph_float32_t
_vglyph_figure_get_cubic_bezier_length(const vglyph_point_t* point0,
                                       const vglyph_point_t* point1,
                                       const vglyph_point_t* point2,
                                       const vglyph_point_t* point3)
{

    vglyph_point_t v01;
    vglyph_point_t v12;
    vglyph_point_t v23;
    vglyph_point_t v03;

    vglyph_float32_t length01 = _vglyph_point_length(_vglyph_point_sub(&v01, point1, point0));
    vglyph_float32_t length12 = _vglyph_point_length(_vglyph_point_sub(&v12, point2, point1));
    vglyph_float32_t length23 = _vglyph_point_length(_vglyph_point_sub(&v23, point3, point2));
    vglyph_float32_t length03 = _vglyph_point_length(_vglyph_point_sub(&v03, point3, point0));
    vglyph_float32_t length   = (length01 + length12 + length23 + length03) * 0.5f;

    return length;
}

vglyph_float32_t
_vglyph_figure_get_arc_length(const vglyph_point_t* radius,
                              const vglyph_point_t* center,
                              vglyph_float32_t cos_fi,
                              vglyph_float32_t sin_fi,
                              vglyph_float32_t theta_0,
                              vglyph_float32_t theta_d)
{
    assert(radius);
    assert(center);
    assert(radius->x != 0.0f);
    assert(radius->y != 0.0f);

    vglyph_float32_t length;
    _vglyph_figure_get_arc_length_and_rect(&length, 
                                           NULL, 
                                           radius, 
                                           center, 
                                           cos_fi, 
                                           sin_fi, 
                                           theta_0, 
                                           theta_d);
    return length;
}

vglyph_rectangle_t*
_vglyph_figure_get_line_rectangle(vglyph_rectangle_t* rectangle,
                                  const vglyph_point_t* point0,
                                  const vglyph_point_t* point1)
{
    assert(rectangle);
    assert(point0);
    assert(point1);

    return _vglyph_rectangle_from_points(rectangle, point0, point1);
}

vglyph_rectangle_t*
_vglyph_figure_get_cubic_bezier_rectangle(vglyph_rectangle_t* rectangle,
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

    _vglyph_rectangle_from_points(rectangle, point0, point3);

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

vglyph_rectangle_t*
_vglyph_figure_get_arc_rectangle(vglyph_rectangle_t* rectangle,
                                 const vglyph_point_t* radius,
                                 const vglyph_point_t* center,
                                 vglyph_float32_t cos_fi,
                                 vglyph_float32_t sin_fi,
                                 vglyph_float32_t theta_0,
                                 vglyph_float32_t theta_d)
{
    assert(rectangle);
    assert(radius);
    assert(center);
    assert(radius->x != 0.0f);
    assert(radius->y != 0.0f);

    _vglyph_figure_get_arc_length_and_rect(NULL, 
                                           rectangle, 
                                           radius, 
                                           center, 
                                           cos_fi, 
                                           sin_fi, 
                                           theta_0, 
                                           theta_d);
    return rectangle;
}

vglyph_rectangle_t*
_vglyph_figure_get_bound(vglyph_figure_t* figure,
                         vglyph_rectangle_t* result)
{
    assert(figure);
    assert(result);

    const vglyph_uint_t size = _vglyph_vector_size_in_bytes(figure->segment_types);

    if (!size)
        return _vglyph_rectangle_from_coord(result, 0.0f, 0.0f, 0.0f, 0.0f);

    if (figure->compute_bound_offset == size)
    {
        *result = figure->bound;
        return result;
    }

    const vglyph_segment_type_t* segment_type;
    const void* segment;

    const vglyph_float32_t pi = 3.14159265358979323846f;
    const vglyph_float32_t degree_to_radians = pi / 180.0f;

    vglyph_bool_t path_closed = TRUE;

    vglyph_rectangle_t bound;
    vglyph_point_t prev_point;
    vglyph_point_t start_point;
    vglyph_point_t point;
    vglyph_point_t point1;
    vglyph_point_t point2;

    vglyph_point_t   radius;
    vglyph_point_t   center;
    vglyph_float32_t cos_fi;
    vglyph_float32_t sin_fi;
    vglyph_float32_t theta_0;
    vglyph_float32_t theta_d;

    prev_point.x = 0.0f;
    prev_point.y = 0.0f;

    figure->compute_bound_offset = 0;
    _vglyph_rectangle_from_coord(&figure->bound, 0.0f, 0.0f, 0.0f, 0.0f);

    while (figure->compute_bound_offset < size)
    {
        segment_type = (vglyph_segment_type_t*)
            _vglyph_vector_at(figure->segment_types, figure->compute_bound_offset);

        segment = _vglyph_vector_at(figure->segments, segment_type->offset);   

        switch (segment_type->segment)
        {
            case VGLYPH_SEGMENT_CLOSEPATH:
                path_closed = TRUE;
                point = start_point;
                goto NEXT_SEGMENT;

            case VGLYPH_SEGMENT_MOVETO_ABS:
            case VGLYPH_SEGMENT_MOVETO_REL:
                _vglyph_figure_offset_point(&point,
                                            &prev_point, 
                                            &((vglyph_segment_moveto_t*)segment)->point, 
                                            segment_type->segment - VGLYPH_SEGMENT_MOVETO_ABS);

                if (path_closed)
                {
                    path_closed = FALSE;
                    start_point = point;

                    goto NEXT_SEGMENT;
                }
                else
                {
                    _vglyph_rectangle_from_points(&bound, &prev_point, &point);
                }
                break;

            case VGLYPH_SEGMENT_LINETO_ABS:
            case VGLYPH_SEGMENT_LINETO_REL:
                _vglyph_figure_offset_point(&point,
                                            &prev_point, 
                                            &((vglyph_segment_lineto_t*)segment)->point, 
                                            segment_type->segment - VGLYPH_SEGMENT_LINETO_ABS);
                _vglyph_rectangle_from_points(&bound, &prev_point, &point);
                break;

            case VGLYPH_SEGMENT_CURVETO_CUBIC_ABS:
            case VGLYPH_SEGMENT_CURVETO_CUBIC_REL:
                _vglyph_figure_offset_point(&point,
                                            &prev_point, 
                                            &((vglyph_segment_curveto_cubic_t*)segment)->point, 
                                            segment_type->segment - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS);
                _vglyph_figure_offset_point(&point1,
                                            &prev_point, 
                                            &((vglyph_segment_curveto_cubic_t*)segment)->point1, 
                                            segment_type->segment - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS);
                _vglyph_figure_offset_point(&point2,
                                            &prev_point, 
                                            &((vglyph_segment_curveto_cubic_t*)segment)->point2, 
                                            segment_type->segment - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS);

                _vglyph_figure_get_cubic_bezier_rectangle(&bound, &prev_point, &point1, &point2, &point);
                break;

            case VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS:
            case VGLYPH_SEGMENT_CURVETO_QUADRATIC_REL:
                break;

            case VGLYPH_SEGMENT_ARC_ABS:
            case VGLYPH_SEGMENT_ARC_REL:
                _vglyph_figure_offset_point(&point,
                                            &prev_point, 
                                            &((vglyph_segment_arc_t*)segment)->point, 
                                            segment_type->segment - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS);

                if (_vglyph_figure_get_arc_params(&radius,
                                                  &center,
                                                  &cos_fi,
                                                  &sin_fi,
                                                  &theta_0,
                                                  &theta_d,
                                                  &prev_point,
                                                  &point,
                                                  &((vglyph_segment_arc_t*)segment)->radius,
                                                  ((vglyph_segment_arc_t*)segment)->angle * degree_to_radians,
                                                  ((vglyph_segment_arc_t*)segment)->large_arc_flag,
                                                  ((vglyph_segment_arc_t*)segment)->sweep_flag))
                {
                    _vglyph_figure_get_arc_rectangle(&bound, &radius, &center, cos_fi, sin_fi, theta_0, theta_d);
                }
                else
                {
                    _vglyph_rectangle_from_points(&bound, &prev_point, &point);
                }
                break;

            case VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS:
            case VGLYPH_SEGMENT_LINETO_HORIZONTAL_REL:
                point.x = segment_type->segment - VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS ?
                    ((vglyph_segment_lineto_horizontal_t*)segment)->x + prev_point.x :
                    ((vglyph_segment_lineto_horizontal_t*)segment)->x;
                point.y = prev_point.y;

                _vglyph_rectangle_from_points(&bound, &prev_point, &point);
                break;

            case VGLYPH_SEGMENT_LINETO_VERTICAL_ABS:
            case VGLYPH_SEGMENT_LINETO_VERTICAL_REL:
                point.x = prev_point.x;
                point.y = segment_type->segment - VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS ?
                    ((vglyph_segment_lineto_vertical_t*)segment)->y + prev_point.y :
                    ((vglyph_segment_lineto_vertical_t*)segment)->y;

                _vglyph_rectangle_from_points(&bound, &prev_point, &point);
                break;

            case VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS:
            case VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_REL:
                break;

            case VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_ABS:
            case VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_REL:
                break;
        }

        _vglyph_figure_bound_union(figure, &bound);

    NEXT_SEGMENT:
        prev_point = point;
        figure->compute_bound_offset += sizeof(vglyph_segment_type_t);
    }

    *result = figure->bound;
    return result;
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

        figure->segment_count        = 0;
        figure->compute_bound_offset = 0;

        return _vglyph_vector_is_valid(figure->segment_types) &&
               _vglyph_vector_is_valid(figure->segments);
    }

    return FALSE;
}

vglyph_bool_t
vglyph_figure_draw_closepath(vglyph_figure_t* figure)
{
    assert(figure);

    if (_vglyph_figure_is_valid(figure))
    {
    #undef  VGLYPH_RESULT_TYPE
    #define VGLYPH_RESULT_TYPE vglyph_segment_closepath_t

        VGLYPH_RESULT_TYPE* result;
        _vglyph_figure_add_segment(
            figure, (vglyph_segment_t)VGLYPH_SEGMENT_CLOSEPATH, result);

        return result ? TRUE : FALSE;
    }

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
