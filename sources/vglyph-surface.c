﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-surface.h"
#include "vglyph-matrix.h"
#include "vglyph-type.h"
#include "vglyph-glyph.h"
#include "vglyph-figure.h"
#include "vglyph-segment-types.h"

static vglyph_point_t* 
_vglyph_surface_offset_point(vglyph_point_t* result,
                             vglyph_surface_t* surface,
                             vglyph_bool_t relative,
                             const vglyph_point_t* prev_point)
{
    result->x *= surface->width;
    result->y *= surface->height;

    if (relative)
    {
        result->x += prev_point->x;
        result->y += prev_point->y;
    }

    return result;
}

static vglyph_state_t 
_vglyph_surface_moveto(vglyph_surface_t* surface,
                       const vglyph_segment_moveto_t* segment,
                       vglyph_bool_t relative,
                       vglyph_vector_t* points,
                       vglyph_point_t* prev_point)
{
    vglyph_point_t point = segment->point;
    _vglyph_surface_offset_point(&point, surface, relative, prev_point);
    *prev_point = point;

    return _vglyph_surface_add_point(points, &point);
}

static vglyph_state_t 
_vglyph_surface_lineto(vglyph_surface_t* surface,
                       const vglyph_segment_lineto_t* segment,
                       vglyph_bool_t relative,
                       vglyph_vector_t* points,
                       vglyph_point_t* prev_point)
{
    vglyph_point_t point = segment->point;
    _vglyph_surface_offset_point(&point, surface, relative, prev_point);
    *prev_point = point;

    return _vglyph_surface_add_point(points, &point);
}

static vglyph_state_t
_vglyph_surface_curveto_cubic(vglyph_surface_t* surface,
                              const vglyph_segment_curveto_cubic_t* segment,
                              vglyph_bool_t relative,
                              vglyph_vector_t* points,
                              vglyph_point_t* prev_point,
                              vglyph_point_t* control_point)
{
    vglyph_render_t* render = surface->render;
    vglyph_state_t   state  = VGLYPH_STATE_SUCCESS;

    vglyph_point_t start  = *prev_point;
    vglyph_point_t end    = segment->point;
    vglyph_point_t point1 = segment->point1;
    vglyph_point_t point2 = segment->point2;

    _vglyph_surface_offset_point(&end,    surface, relative, prev_point);
    _vglyph_surface_offset_point(&point1, surface, relative, prev_point);
    _vglyph_surface_offset_point(&point2, surface, relative, prev_point);

    *prev_point = end;
    *control_point = point2;

    const vglyph_float32_t length = 
        _vglyph_figure_get_cubic_bezier_length(&start, &point1, &point2, &end);

    const vglyph_float32_t dt = 1.0f / length * 4.0f;

    vglyph_point_t old_point = start;
    vglyph_point_t new_point;

    vglyph_bool_t b_end = FALSE;

    for (vglyph_float32_t t = dt;; t += dt)
    {
        if (t >= 1.0f)
        {
            t = 1.0f;
            b_end = TRUE;
        }

        _vglyph_figure_cubic_bezier(&new_point, &start, &point1, &point2, &end, t);

        vglyph_point_t v;
        _vglyph_point_sub(&v, &new_point, &old_point);

        const vglyph_float32_t line_length = _vglyph_point_length(&v);

        if (!b_end && line_length < 1.0f)
            continue;

        state = _vglyph_surface_add_point(points, &new_point);
        old_point = new_point;

        if (state != VGLYPH_STATE_SUCCESS)
            return state;

        if (b_end)
            break;
    }

    return state;
}

static vglyph_state_t
_vglyph_surface_curveto_quadratic(vglyph_surface_t* surface,
                                  const vglyph_segment_curveto_quadratic_t* segment,
                                  vglyph_bool_t relative,
                                  vglyph_vector_t* points,
                                  vglyph_point_t* prev_point,
                                  vglyph_point_t* control_point)
{
    vglyph_render_t* render = surface->render;
    vglyph_state_t   state  = VGLYPH_STATE_SUCCESS;

    vglyph_point_t start  = *prev_point;
    vglyph_point_t end    = segment->point;
    vglyph_point_t point1 = segment->point1;

    _vglyph_surface_offset_point(&end,    surface, relative, prev_point);
    _vglyph_surface_offset_point(&point1, surface, relative, prev_point);

    *prev_point = end;
    *control_point = point1;

    const vglyph_float32_t length = 
        _vglyph_figure_get_quadratic_bezier_length(&start, &point1, &end);

    const vglyph_float32_t dt = 1.0f / length * 4.0f;

    vglyph_point_t old_point = start;
    vglyph_point_t new_point;

    vglyph_bool_t b_end = FALSE;

    for (vglyph_float32_t t = dt;; t += dt)
    {
        if (t >= 1.0f)
        {
            t = 1.0f;
            b_end = TRUE;
        }

        _vglyph_figure_quadratic_bezier(&new_point, &start, &point1, &end, t);

        vglyph_point_t v;
        _vglyph_point_sub(&v, &new_point, &old_point);

        const vglyph_float32_t line_length = _vglyph_point_length(&v);

        if (!b_end && line_length < 1.0f)
            continue;

        state = _vglyph_surface_add_point(points, &new_point);
        old_point = new_point;

        if (state != VGLYPH_STATE_SUCCESS)
            return state;

        if (b_end)
            break;
    }

    return state;
}

static vglyph_state_t 
_vglyph_surface_arc(vglyph_surface_t* surface,
                    const vglyph_segment_arc_t* segment,
                    vglyph_bool_t relative,
                    vglyph_vector_t* points,
                    vglyph_point_t* prev_point)
{
    if (segment->radius.x == 0.0f || segment->radius.y == 0.0f)
    {
        vglyph_segment_lineto_t line_segment;
        line_segment.point = segment->point;

        return _vglyph_surface_lineto(surface, &line_segment, relative, points, prev_point);
    }

    vglyph_state_t state = VGLYPH_STATE_SUCCESS;

    vglyph_point_t   radius;
    vglyph_point_t   center;
    vglyph_float32_t cos_fi;
    vglyph_float32_t sin_fi;
    vglyph_float32_t theta_0;
    vglyph_float32_t theta_d;

    const vglyph_float32_t pi = 3.14159265358979323846f;
    const vglyph_float32_t degree_to_radians = pi / 180.0f;

    vglyph_point_t start = *prev_point;
    vglyph_point_t end   = segment->point;

    _vglyph_surface_offset_point(&end, surface, relative, prev_point);
    *prev_point = end;

    radius.x = segment->radius.x * surface->width;
    radius.y = segment->radius.y * surface->height;

    _vglyph_figure_get_arc_params(&radius, 
                                  &center, 
                                  &cos_fi, 
                                  &sin_fi, 
                                  &theta_0, 
                                  &theta_d,
                                  &start, 
                                  &end, 
                                  &radius, 
                                  segment->angle * degree_to_radians, 
                                  segment->large_arc_flag,
                                  segment->sweep_flag);

    const vglyph_float32_t length = _vglyph_figure_get_arc_length(&radius, 
                                                                  &center, 
                                                                  cos_fi, 
                                                                  sin_fi, 
                                                                  theta_0, 
                                                                  theta_d);

    const vglyph_uint32_t count_part = (vglyph_uint32_t)ceilf(length * 0.5f);
    const vglyph_float32_t dt = theta_d / count_part;

    vglyph_float32_t theta;
    vglyph_point_t   point;

    for (vglyph_uint32_t part = 1; part <= count_part; ++part)
    {
        theta = theta_0 + (part == count_part ? theta_d : dt * part);

        _vglyph_figure_arc(&point, &radius, &center, cos_fi, sin_fi, theta);

        state = _vglyph_surface_add_point(points, &point);

        if (state != VGLYPH_STATE_SUCCESS)
            return state;
    }

    return state;
}

static vglyph_state_t 
_vglyph_surface_lineto_horizontal(vglyph_surface_t* surface,
                                  const vglyph_segment_lineto_horizontal_t* segment,
                                  vglyph_bool_t relative,
                                  vglyph_vector_t* points,
                                  vglyph_point_t* prev_point)
{
    vglyph_segment_lineto_t line_segment;

    _vglyph_point_from_coord(&line_segment.point, 
                             segment->x, 
                             relative ? 0.0f : prev_point->y);

    return _vglyph_surface_lineto(surface, &line_segment, relative, points, prev_point);
}

static vglyph_state_t 
_vglyph_surface_lineto_vertical(vglyph_surface_t* surface,
                                const vglyph_segment_lineto_vertical_t* segment,
                                vglyph_bool_t relative,
                                vglyph_vector_t* points,
                                vglyph_point_t* prev_point)
{
    vglyph_segment_lineto_t line_segment;

    _vglyph_point_from_coord(&line_segment.point, 
                             relative ? 0.0f : prev_point->x,
                             segment->y);

    return _vglyph_surface_lineto(surface, &line_segment, relative, points, prev_point);
}

static vglyph_state_t
_vglyph_surface_curveto_cubic_smooth(vglyph_surface_t* surface,
                                     const vglyph_segment_curveto_cubic_smooth_t* segment,
                                     vglyph_bool_t relative,
                                     vglyph_vector_t* points,
                                     vglyph_point_t* prev_point,
                                     vglyph_point_t* control_point)
{
    vglyph_point_t v;

    if (control_point->x != control_point->x)
        _vglyph_point_from_coord(&v, 0.0f, 0.0f);
    else
        _vglyph_point_sub(&v, prev_point, control_point);

    if (!relative)
        _vglyph_point_add(&v, prev_point, &v);

    v.x /= surface->width;
    v.y /= surface->height;

    vglyph_segment_curveto_cubic_t cubic_segment;
    cubic_segment.point  = segment->point;
    cubic_segment.point1 = v;
    cubic_segment.point2 = segment->point2;

    return _vglyph_surface_curveto_cubic(surface,
                                         &cubic_segment,
                                         relative,
                                         points,
                                         prev_point,
                                         control_point);
}

static vglyph_state_t
_vglyph_surface_curveto_quadratic_smooth(vglyph_surface_t* surface,
                                         const vglyph_segment_curveto_quadratic_smooth_t* segment,
                                         vglyph_bool_t relative,
                                         vglyph_vector_t* points,
                                         vglyph_point_t* prev_point,
                                         vglyph_point_t* control_point)
{
    vglyph_point_t v;

    if (control_point->x != control_point->x)
        _vglyph_point_from_coord(&v, 0.0f, 0.0f);
    else
        _vglyph_point_sub(&v, prev_point, control_point);

    if (!relative)
        _vglyph_point_add(&v, prev_point, &v);

    v.x /= surface->width;
    v.y /= surface->height;

    vglyph_segment_curveto_quadratic_t quadratic_segment;
    quadratic_segment.point  = segment->point;
    quadratic_segment.point1 = v;

    return _vglyph_surface_curveto_quadratic(surface,
                                             &quadratic_segment,
                                             relative,
                                             points,
                                             prev_point,
                                             control_point);
}

static vglyph_state_t
_vglyph_surface_segment_to_lines(vglyph_surface_t* surface,
                                 vglyph_segment_t segment_type,
                                 const void* segment,
                                 vglyph_vector_t* points,
                                 vglyph_bool_t* path_closed,
                                 vglyph_point_t* start_point,
                                 vglyph_point_t* prev_point,
                                 vglyph_point_t* control_point)
{
    vglyph_state_t state = VGLYPH_STATE_SUCCESS;

    if (*path_closed && (segment_type != VGLYPH_SEGMENT_MOVETO_ABS &&
                         segment_type != VGLYPH_SEGMENT_MOVETO_REL))
    {
        *path_closed = FALSE;
        *start_point = *prev_point;
        
        if ((state = _vglyph_surface_add_point(points, prev_point)) != VGLYPH_STATE_SUCCESS)
            return state;
    }

    switch (segment_type)
    {
        case VGLYPH_SEGMENT_CLOSEPATH:
            if (!(*path_closed))
            {
                *path_closed = TRUE;

                if (prev_point->x != start_point->x ||
                    prev_point->y != start_point->y)
                {
                    prev_point = start_point;
                    state = _vglyph_surface_add_point(points, start_point);

                    if (state != VGLYPH_STATE_SUCCESS)
                        return state;
                }

                vglyph_point_t end_marker;
                _vglyph_point_from_coord(&end_marker, NAN, NAN);

                return _vglyph_surface_add_point(points, &end_marker);
            }
            break;

        case VGLYPH_SEGMENT_MOVETO_ABS:
        case VGLYPH_SEGMENT_MOVETO_REL:
            state = _vglyph_surface_moveto(surface,
                                           (vglyph_segment_moveto_t*)segment,
                                           segment_type - VGLYPH_SEGMENT_MOVETO_ABS,
                                           points,
                                           prev_point);

            if (*path_closed)
            {
                *path_closed = FALSE;
                *start_point = *prev_point;
            }
            break;

        case VGLYPH_SEGMENT_LINETO_ABS:
        case VGLYPH_SEGMENT_LINETO_REL:
            return _vglyph_surface_lineto(surface,
                                          (vglyph_segment_lineto_t*)segment,
                                          segment_type - VGLYPH_SEGMENT_LINETO_ABS,
                                          points,
                                          prev_point);

        case VGLYPH_SEGMENT_CURVETO_CUBIC_ABS:
        case VGLYPH_SEGMENT_CURVETO_CUBIC_REL:
            return _vglyph_surface_curveto_cubic(surface,
                                                 (vglyph_segment_curveto_cubic_t*)segment,
                                                 segment_type - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS,
                                                 points,
                                                 prev_point,
                                                 control_point);

        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS:
        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_REL:
            return _vglyph_surface_curveto_quadratic(surface,
                                                     (vglyph_segment_curveto_quadratic_t*)segment,
                                                     segment_type - VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS,
                                                     points,
                                                     prev_point,
                                                     control_point);
            break;

        case VGLYPH_SEGMENT_ARC_ABS:
        case VGLYPH_SEGMENT_ARC_REL:
            return _vglyph_surface_arc(surface,
                                       (vglyph_segment_arc_t*)segment,
                                       segment_type - VGLYPH_SEGMENT_ARC_ABS,
                                       points,
                                       prev_point);

        case VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS:
        case VGLYPH_SEGMENT_LINETO_HORIZONTAL_REL:
            return _vglyph_surface_lineto_horizontal(surface,
                                                     (vglyph_segment_lineto_horizontal_t*)segment,
                                                     segment_type - VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS,
                                                     points,
                                                     prev_point);

        case VGLYPH_SEGMENT_LINETO_VERTICAL_ABS:
        case VGLYPH_SEGMENT_LINETO_VERTICAL_REL:
            return _vglyph_surface_lineto_vertical(surface,
                                                   (vglyph_segment_lineto_vertical_t*)segment,
                                                   segment_type - VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS,
                                                   points,
                                                   prev_point);

        case VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS:
        case VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_REL:
            return _vglyph_surface_curveto_cubic_smooth(surface,
                                                        (vglyph_segment_curveto_cubic_smooth_t*)segment,
                                                        segment_type - VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS,
                                                        points,
                                                        prev_point,
                                                        control_point);

        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_ABS:
        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_REL:
            return _vglyph_surface_curveto_quadratic_smooth(surface,
                                                            (vglyph_segment_curveto_quadratic_smooth_t*)segment,
                                                            segment_type - VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_ABS,
                                                            points,
                                                            prev_point,
                                                            control_point);
    }

    return state;
}

static vglyph_vector_t*
_vglyph_surface_figure_to_lines(vglyph_surface_t* surface,
                                vglyph_figure_t* figure,
                                vglyph_state_t* state)
{
    *state = VGLYPH_STATE_SUCCESS;

    vglyph_uint_t segment_count = figure->segment_count;
    vglyph_uint_t offset_segment_type = 0;

    vglyph_vector_t* result = _vglyph_vector_create(sizeof(vglyph_point_t) * segment_count);

    if (!segment_count)
        return result;

    const vglyph_segment_type_t* segment_type = NULL;
    const void* segment;

    vglyph_bool_t path_closed = TRUE;

    vglyph_point_t prev_point;
    vglyph_point_t start_point;
    vglyph_point_t control_point;

    prev_point.x = 0.0f;
    prev_point.y = 0.0f;
    control_point.x = NAN;
    control_point.y = NAN;

    while (segment_count--)
    {
        segment_type = (vglyph_segment_type_t*)
            _vglyph_vector_at(figure->segment_types, offset_segment_type);

        segment = _vglyph_vector_at(figure->segments, segment_type->offset);  

        if ((segment_type->segment < VGLYPH_SEGMENT_CURVETO_CUBIC_ABS || 
             segment_type->segment > VGLYPH_SEGMENT_CURVETO_QUADRATIC_REL) &&
            (segment_type->segment < VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS || 
             segment_type->segment > VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_REL))
            _vglyph_point_from_coord(&control_point, NAN, NAN);

        *state = _vglyph_surface_segment_to_lines(surface, 
                                                  segment_type->segment, 
                                                  segment, result, 
                                                  &path_closed, 
                                                  &start_point, 
                                                  &prev_point,
                                                  &control_point);

        if (*state != VGLYPH_STATE_SUCCESS)
            return result;

        offset_segment_type += sizeof(vglyph_segment_type_t);
    }

    if (segment_type->segment != VGLYPH_SEGMENT_CLOSEPATH)
    {
        vglyph_segment_closepath_t closepath;
        *state = _vglyph_surface_segment_to_lines(surface, 
                                                  VGLYPH_SEGMENT_CLOSEPATH, 
                                                  &closepath, 
                                                  result, 
                                                  &path_closed, 
                                                  &start_point, 
                                                  &prev_point,
                                                  &control_point);
    }

    return result;
}

static vglyph_vector_t**
_vglyph_surface_compute_intersections(vglyph_surface_t* surface,
                                      vglyph_vector_t* points,
                                      vglyph_state_t* state)
{
    *state = VGLYPH_STATE_SUCCESS;

    const vglyph_uint32_t height = surface->height;
    vglyph_vector_t** intersections = malloc(sizeof(vglyph_vector_t*) * height);

    if (!intersections)
    {
        *state = VGLYPH_STATE_OUT_OF_MEMORY;
        return NULL;
    }

    for (vglyph_uint32_t y = 0; y < height; ++y)
        intersections[y] = NULL;

    const vglyph_uint_t size = _vglyph_vector_size_in_bytes(points);
    vglyph_point_t start = *((vglyph_point_t*)_vglyph_vector_at(points, 0));
    vglyph_point_t end;

    for (vglyph_uint_t offset = sizeof(vglyph_point_t); offset < size; offset += sizeof(vglyph_point_t))
    {
        end = *((vglyph_point_t*)_vglyph_vector_at(points, offset));

        if (end.x != end.x)
        {
            offset += sizeof(vglyph_point_t);

            if (offset == size)
                break;

            start = *((vglyph_point_t*)_vglyph_vector_at(points, offset));
            continue;
        }
        
        vglyph_point_t start_point;
        vglyph_point_t end_point;

        if (start.y > end.y)
        {
            start_point = end;
            end_point   = start;
        }
        else
        {
            start_point = start;
            end_point   = end;
        }

        vglyph_point_t v;
        _vglyph_point_sub(&v, &end_point, &start_point);

        vglyph_sint_t start_y = (vglyph_sint_t)floorf(start_point.y);
        vglyph_sint_t end_y   = start_y + (vglyph_sint_t)ceilf(v.y) + 1;

        vglyph_float32_t t;
        vglyph_float32_t inv_d = 1.0f / v.y;

        for (vglyph_sint_t y = start_y; y < end_y; ++y)
        {
            t = (y - start_point.y) * inv_d;

            if (t >= 0.0f && t < 1.0f)
            {
                if (!intersections[y])
                {
                    vglyph_vector_t* item = _vglyph_vector_create(sizeof(vglyph_float32_t) << 3);

                    if (!_vglyph_vector_is_valid(item))
                    {
                        *state = _vglyph_vector_get_state(item);
                        _vglyph_vector_destroy(item);

                        return intersections;
                    }

                    intersections[y] = item;
                }

                vglyph_float32_t intersection_x = start_point.x + v.x * t;
                vglyph_float32_t intersection_current;

                vglyph_uint_t count_intersections = _vglyph_vector_size_in_bytes(intersections[y]);
                vglyph_uint_t find_offset;

                for (find_offset = 0; find_offset < count_intersections; find_offset += sizeof(vglyph_float32_t))
                {
                    intersection_current = *(vglyph_float32_t*)_vglyph_vector_at(intersections[y], find_offset);

                    if (intersection_x < intersection_current)
                        break;
                }

                _vglyph_vector_insert(intersections[y], 
                                      (vglyph_uint8_t*)&intersection_x, 
                                      sizeof(vglyph_float32_t), 
                                      find_offset);
            }
        }

        start = end;
    }

    return intersections;
}

static void 
_vglyph_surface_draw_polygon(vglyph_surface_t* surface,
                             vglyph_vector_t** intersections,
                             const vglyph_color_t* color)
{
    vglyph_render_t* render = surface->render;

    void (*set_pixel)(vglyph_render_t*,
                      vglyph_surface_t*,
                      vglyph_sint32_t,
                      vglyph_sint32_t,
                      const vglyph_color_t*) = color->alpha < 1.0 ? 
        render->backend->alpha_blend : 
        render->backend->set_pixel;

    const vglyph_uint32_t height = surface->height;
    const vglyph_uint_t offset_1 = sizeof(vglyph_float32_t);
    const vglyph_uint_t offset_2 = sizeof(vglyph_float32_t) << 1;

    vglyph_float32_t s_x;
    vglyph_float32_t e_x;

    vglyph_fixed_t x;
    vglyph_fixed_t fx;
    vglyph_fixed_t cx;

    vglyph_sint32_t s_ix;
    vglyph_sint32_t e_ix;

    vglyph_color_t result_color;
    result_color.red   = color->red;
    result_color.green = color->green;
    result_color.blue  = color->blue;
    double alpha;

    for (vglyph_uint32_t y = 0; y < height; ++y)
    { 
        if (intersections[y])
        {
            const vglyph_uint_t count_intersections = _vglyph_vector_size_in_bytes(intersections[y]);

            for (vglyph_uint_t i = 0; i < count_intersections; i += offset_2)
            {
                s_x = *(vglyph_float32_t*)_vglyph_vector_at(intersections[y], i);
                e_x = *(vglyph_float32_t*)_vglyph_vector_at(intersections[y], i + offset_1);

                x  = _vglyph_fixed_from_float32(s_x);
                fx = _vglyph_fixed_floor(x);
                cx = _vglyph_fixed_ceil(x);

                s_ix = _vglyph_fixed_to_sint32_floor(fx);

                if (fx != cx)
                {
                    alpha = _vglyph_fixed_to_float32(cx - x);
                    result_color.alpha = color->alpha * alpha;

                    render->backend->alpha_blend(render, surface, s_ix, y, &result_color);
                    ++s_ix;
                }

                x  = _vglyph_fixed_from_float32(e_x);
                fx = _vglyph_fixed_floor(x);
                cx = _vglyph_fixed_ceil(x);

                e_ix = _vglyph_fixed_to_sint32_ceil(cx);

                if (fx != cx)
                {
                    alpha = _vglyph_fixed_to_float32(x - fx);
                    result_color.alpha = color->alpha * alpha;

                    render->backend->alpha_blend(render, surface, e_ix - 1, y, &result_color);
                    --e_ix;
                }

                for (vglyph_sint32_t x = s_ix; x < e_ix; ++x)
                    set_pixel(render, surface, x, y, color);
            }
        }
    }
}

void
_vglyph_surface_init(vglyph_surface_t* surface,
                     const vglyph_object_backend_t* object_backend,
                     const vglyph_surface_backend_t* surface_backend,
                     vglyph_format_t* format,
                     vglyph_render_t* render,
                     vglyph_uint32_t width,
                     vglyph_uint32_t height,
                     vglyph_uint32_t pitch)
{
    assert(surface);
    assert(object_backend);
    assert(surface_backend);
    assert(format);
    assert(render);

    _vglyph_object_init(&surface->object, object_backend);

    surface->backend = surface_backend;
    surface->format  = _vglyph_format_reference(format);
    surface->render  = _vglyph_render_reference(render);
    surface->width   = width;
    surface->height  = height;
    surface->pitch   = pitch;
}

void
_vglyph_surface_ctor(vglyph_surface_t* surface)
{
    if (!_vglyph_format_is_valid(surface->format))
    {
        _vglyph_surface_set_state(surface, _vglyph_format_get_state(surface->format));
        return;
    }

    if (!_vglyph_render_is_valid(surface->render))
    {
        _vglyph_surface_set_state(surface, _vglyph_render_get_state(surface->render));
        return;
    }
}

void
_vglyph_surface_dtor(vglyph_surface_t* surface)
{
    _vglyph_render_destroy(surface->render);
    _vglyph_format_destroy(surface->format);
}

vglyph_bool_t
_vglyph_surface_is_cast(vglyph_type_t* type)
{
    return vglyph_get_surface_type() == type;
}

static void
_vglyph_surface_destroy(vglyph_object_t* object)
{
    vglyph_surface_t* surface = (vglyph_surface_t*)object;
    _vglyph_surface_dtor(surface);

    free(surface);
}

static const vglyph_object_backend_t vglyph_surface_object_backend = {
    vglyph_get_surface_type,
    _vglyph_surface_is_cast,
    _vglyph_surface_destroy
};

vglyph_type_t*
vglyph_get_surface_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_surface_is_cast);
    return &type;
}

vglyph_surface_t*
vglyph_object_to_surface(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_surface_t*)_vglyph_object_to_type(object, vglyph_get_surface_type());
}

vglyph_object_t*
vglyph_surface_to_object(vglyph_surface_t* surface)
{
    assert(surface);
    return &surface->object;
}

vglyph_format_t*
vglyph_surface_get_format(vglyph_surface_t* surface)
{
    assert(surface);
    return _vglyph_format_reference(surface->format);
}

vglyph_uint32_t
vglyph_surface_get_width(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->width;

    return 0;
}

vglyph_uint32_t
vglyph_surface_get_height(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->height;

    return 0;
}

vglyph_uint32_t
vglyph_surface_get_pitch(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        return surface->pitch;

    return 0;
}

vglyph_uint8_t*
vglyph_surface_lock(vglyph_surface_t* surface,
                    vglyph_uint32_t x,
                    vglyph_uint32_t y,
                    vglyph_uint32_t width,
                    vglyph_uint32_t height)
{
    assert(surface);
    assert(x >= 0);
    assert(y >= 0);
    assert(x + width <= surface->width);
    assert(y + height <= surface->height);

    if (_vglyph_surface_is_valid(surface))
        return surface->backend->lock(surface, x, y, width, height);

    return NULL;
}

void
vglyph_surface_unlock(vglyph_surface_t* surface)
{
    assert(surface);

    if (_vglyph_surface_is_valid(surface))
        surface->backend->unlock(surface);
}

void
vglyph_surface_fill(vglyph_surface_t* surface,
                    vglyph_uint32_t x,
                    vglyph_uint32_t y,
                    vglyph_uint32_t width,
                    vglyph_uint32_t height,
                    const vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        vglyph_render_t* render = surface->render;
        render->backend->fill(render, surface, x, y, width, height, color);
    }
}

void
vglyph_surface_get_pixel(vglyph_surface_t* surface,
                         vglyph_sint32_t x,
                         vglyph_sint32_t y,
                         vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        vglyph_render_t* render = surface->render;
        render->backend->get_pixel(render, surface, x, y, color);
    }
}

void
vglyph_surface_set_pixel(vglyph_surface_t* surface,
                         vglyph_sint32_t x,
                         vglyph_sint32_t y,
                         const vglyph_color_t* color)
{
    assert(surface);
    assert(color);

    if (_vglyph_surface_is_valid(surface))
    {
        vglyph_render_t* render = surface->render;
        render->backend->set_pixel(render, surface, x, y, color);
    }
}

void
vglyph_surface_draw_glyph(vglyph_surface_t* surface,
                          vglyph_glyph_t* glyph,
                          const vglyph_color_t* color,
                          const vglyph_point_t* position,
                          const vglyph_point_t* origin,
                          vglyph_float32_t radians)
{
    assert(surface);
    assert(glyph);

    //vglyph_matrix_t mat;
    //_vglyph_matrix_identity(&mat);

    //if (origin)
    //    _vglyph_matrix_translate(&mat, &mat, origin->x, origin->y);

    //if (radians != 0.0f)
    //    _vglyph_matrix_rotate(&mat, &mat, radians);

    //if (position)
    //    _vglyph_matrix_translate(&mat, &mat, position->x, position->y);

    vglyph_state_t state;
    vglyph_vector_t* points = _vglyph_surface_figure_to_lines(surface, glyph->figure, &state);

    if (state == VGLYPH_STATE_SUCCESS)
    {
        vglyph_vector_t** intersections = _vglyph_surface_compute_intersections(surface, points, &state);
        _vglyph_vector_destroy(points);

        if (state == VGLYPH_STATE_SUCCESS)
            _vglyph_surface_draw_polygon(surface, intersections, color);
        else
            _vglyph_surface_set_state(surface, state);

        if (intersections)
        {
            const vglyph_uint32_t height = surface->height;

            for (vglyph_uint32_t y = 0; y < height; ++y)
            {
                if (intersections[y])
                    _vglyph_vector_destroy(intersections[y]);
            }

            free(intersections);
        }
    }
    else
    {
        _vglyph_surface_set_state(surface, state);
        _vglyph_vector_destroy(points);
    }
}
