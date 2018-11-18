/* vglyph - library for visualize glyphs
 *
 * File: vglyph-data-surface.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-data-surface.h"
#include "vglyph-rgba-uint-format.h"
#include "vglyph-rgba-uint-data-render.h"
#include "vglyph-rgba-little-uint-data-render.h"
#include "vglyph-rgba-uint16-data-render.h"
#include "vglyph-rgba-uint32-data-render.h"
#include "vglyph-type.h"
#include "vglyph-glyph.h"
#include "vglyph-figure.h"
#include "vglyph-segment-types.h"

static vglyph_point_t* 
_vglyph_data_surface_offset_point(vglyph_point_t* result,
                                  vglyph_data_surface_t* surface,
                                  vglyph_bool_t relative,
                                  const vglyph_point_t* prev_point)
{
    result->x *= surface->base.width  << surface->shift_mulitsampling;
    result->y *= surface->base.height << surface->shift_mulitsampling;

    if (relative)
    {
        result->x += prev_point->x;
        result->y += prev_point->y;
    }

    return result;
}

static vglyph_state_t
_vglyph_data_surface_moveto(vglyph_data_surface_t* surface,
                            const vglyph_segment_moveto_t* segment,
                            const vglyph_matrix_t* matrix,
                            vglyph_bool_t relative,
                            vglyph_vector_t* points,
                            vglyph_point_t* prev_point)
{
    vglyph_point_t point = segment->point;
    _vglyph_data_surface_offset_point(&point, surface, relative, prev_point);
    *prev_point = point;

    return _vglyph_data_surface_add_point(points, matrix, &point);
}

static vglyph_state_t 
_vglyph_data_surface_lineto(vglyph_data_surface_t* surface,
                            const vglyph_segment_lineto_t* segment,
                            const vglyph_matrix_t* matrix,
                            vglyph_bool_t relative,
                            vglyph_vector_t* points,
                            vglyph_point_t* prev_point)
{
    vglyph_point_t point = segment->point;
    _vglyph_data_surface_offset_point(&point, surface, relative, prev_point);
    *prev_point = point;

    return _vglyph_data_surface_add_point(points, matrix, &point);
}

static vglyph_state_t
_vglyph_data_surface_curveto_cubic(vglyph_data_surface_t* surface,
                                   const vglyph_segment_curveto_cubic_t* segment,
                                   const vglyph_matrix_t* matrix,
                                   vglyph_bool_t relative,
                                   vglyph_vector_t* points,
                                   vglyph_point_t* prev_point,
                                   vglyph_point_t* control_point)
{
    vglyph_state_t state = VGLYPH_STATE_SUCCESS;

    vglyph_point_t start  = *prev_point;
    vglyph_point_t end    = segment->point;
    vglyph_point_t point1 = segment->point1;
    vglyph_point_t point2 = segment->point2;

    _vglyph_data_surface_offset_point(&end,    surface, relative, prev_point);
    _vglyph_data_surface_offset_point(&point1, surface, relative, prev_point);
    _vglyph_data_surface_offset_point(&point2, surface, relative, prev_point);

    *prev_point = end;
    *control_point = point2;

    const vglyph_float32_t length = 
        _vglyph_figure_get_cubic_bezier_length(&start, &point1, &point2, &end);

    const vglyph_float32_t dt = 1.0f / length * 4.0f;
    
    vglyph_point_t old_point = start;
    vglyph_point_t new_point;
    vglyph_point_t vec;

    for (vglyph_float32_t t = dt; t < 1.0f; t += dt)
    {
        _vglyph_figure_cubic_bezier(&new_point, &start, &point1, &point2, &end, t);
        _vglyph_point_sub(&vec, &new_point, &old_point);

        if (_vglyph_point_length_square(&vec) < 1.0f)
            continue;

        state = _vglyph_data_surface_add_point(points, matrix, &new_point);
        old_point = new_point;

        if (state != VGLYPH_STATE_SUCCESS)
            return state;
    }

    state = _vglyph_data_surface_add_point(points, matrix, &end);
    return state;
}

static vglyph_state_t
_vglyph_data_surface_curveto_quadratic(vglyph_data_surface_t* surface,
                                       const vglyph_segment_curveto_quadratic_t* segment,
                                       const vglyph_matrix_t* matrix,
                                       vglyph_bool_t relative,
                                       vglyph_vector_t* points,
                                       vglyph_point_t* prev_point,
                                       vglyph_point_t* control_point)
{
    vglyph_state_t state = VGLYPH_STATE_SUCCESS;

    vglyph_point_t start  = *prev_point;
    vglyph_point_t end    = segment->point;
    vglyph_point_t point1 = segment->point1;

    _vglyph_data_surface_offset_point(&end,    surface, relative, prev_point);
    _vglyph_data_surface_offset_point(&point1, surface, relative, prev_point);

    *prev_point = end;
    *control_point = point1;

    const vglyph_float32_t length = 
        _vglyph_figure_get_quadratic_bezier_length(&start, &point1, &end);

    const vglyph_float32_t dt = 1.0f / length * 4.0f;

    vglyph_point_t old_point = start;
    vglyph_point_t new_point;
    vglyph_point_t vec;

    for (vglyph_float32_t t = dt; t < 1.0f; t += dt)
    {
        _vglyph_figure_quadratic_bezier(&new_point, &start, &point1, &end, t);
        _vglyph_point_sub(&vec, &new_point, &old_point);

        if (_vglyph_point_length_square(&vec) < 1.0f)
            continue;

        state = _vglyph_data_surface_add_point(points, matrix, &new_point);
        old_point = new_point;

        if (state != VGLYPH_STATE_SUCCESS)
            return state;
    }

    state = _vglyph_data_surface_add_point(points, matrix, &end);
    return state;
}

static vglyph_state_t 
_vglyph_data_surface_arc(vglyph_data_surface_t* surface,
                         const vglyph_segment_arc_t* segment,
                         const vglyph_matrix_t* matrix,
                         vglyph_bool_t relative,
                         vglyph_vector_t* points,
                         vglyph_point_t* prev_point)
{
    if (segment->radius.x == 0.0f || segment->radius.y == 0.0f)
    {
        vglyph_segment_lineto_t line_segment;
        line_segment.point = segment->point;

        return _vglyph_data_surface_lineto(surface, &line_segment, matrix, relative, points, prev_point);
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

    _vglyph_data_surface_offset_point(&end, surface, relative, prev_point);
    *prev_point = end;

    radius.x = segment->radius.x * (surface->base.width  << surface->shift_mulitsampling);
    radius.y = segment->radius.y * (surface->base.height << surface->shift_mulitsampling);

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

    const vglyph_uint32_t count_part = (vglyph_uint32_t)ceilf(length * 0.5f) - 1;
    const vglyph_float32_t dt = theta_d / count_part;

    vglyph_float32_t theta;
    vglyph_point_t   point;

    for (vglyph_uint32_t part = 1; part < count_part; ++part)
    {
        theta = theta_0 + dt * part;

        _vglyph_figure_arc(&point, &radius, &center, cos_fi, sin_fi, theta);

        state = _vglyph_data_surface_add_point(points, matrix, &point);

        if (state != VGLYPH_STATE_SUCCESS)
            return state;
    }

    state = _vglyph_data_surface_add_point(points, matrix, &end);
    return state;
}

static vglyph_state_t
_vglyph_data_surface_lineto_horizontal(vglyph_data_surface_t* surface,
                                       const vglyph_segment_lineto_horizontal_t* segment,
                                       const vglyph_matrix_t* matrix,
                                       vglyph_bool_t relative,
                                       vglyph_vector_t* points,
                                       vglyph_point_t* prev_point)
{
    vglyph_segment_lineto_t line_segment;

    _vglyph_point_from_coord(&line_segment.point, 
                             segment->x, 
                             relative ? 0.0f : prev_point->y);

    return _vglyph_data_surface_lineto(surface, &line_segment, matrix, relative, points, prev_point);
}

static vglyph_state_t
_vglyph_data_surface_lineto_vertical(vglyph_data_surface_t* surface,
                                     const vglyph_segment_lineto_vertical_t* segment,
                                     const vglyph_matrix_t* matrix,
                                     vglyph_bool_t relative,
                                     vglyph_vector_t* points,
                                     vglyph_point_t* prev_point)
{
    vglyph_segment_lineto_t line_segment;

    _vglyph_point_from_coord(&line_segment.point, 
                             relative ? 0.0f : prev_point->x,
                             segment->y);

    return _vglyph_data_surface_lineto(surface, &line_segment, matrix, relative, points, prev_point);
}

static vglyph_state_t
_vglyph_data_surface_curveto_cubic_smooth(vglyph_data_surface_t* surface,
                                          const vglyph_segment_curveto_cubic_smooth_t* segment,
                                          const vglyph_matrix_t* matrix,
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

    v.x /= surface->base.width  << surface->shift_mulitsampling;
    v.y /= surface->base.height << surface->shift_mulitsampling;

    vglyph_segment_curveto_cubic_t cubic_segment;
    cubic_segment.point  = segment->point;
    cubic_segment.point1 = v;
    cubic_segment.point2 = segment->point2;

    return _vglyph_data_surface_curveto_cubic(surface,
                                              &cubic_segment,
                                              matrix,
                                              relative,
                                              points,
                                              prev_point,
                                              control_point);
}

static vglyph_state_t
_vglyph_data_surface_curveto_quadratic_smooth(vglyph_data_surface_t* surface,
                                              const vglyph_segment_curveto_quadratic_smooth_t* segment,
                                              const vglyph_matrix_t* matrix,
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

    v.x /= surface->base.width  << surface->shift_mulitsampling;
    v.y /= surface->base.height << surface->shift_mulitsampling;

    vglyph_segment_curveto_quadratic_t quadratic_segment;
    quadratic_segment.point  = segment->point;
    quadratic_segment.point1 = v;

    return _vglyph_data_surface_curveto_quadratic(surface,
                                                  &quadratic_segment,
                                                  matrix,
                                                  relative,
                                                  points,
                                                  prev_point,
                                                  control_point);
}

static vglyph_state_t
_vglyph_data_surface_segment_to_lines(vglyph_data_surface_t* surface,
                                      vglyph_segment_t segment_type,
                                      const void* segment,
                                      const vglyph_matrix_t* matrix,
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
        
        if ((state = _vglyph_data_surface_add_point(points, matrix, prev_point)) != VGLYPH_STATE_SUCCESS)
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
                    state = _vglyph_data_surface_add_point(points, matrix, start_point);

                    if (state != VGLYPH_STATE_SUCCESS)
                        return state;
                }

                vglyph_point_t end_marker;
                _vglyph_point_from_coord(&end_marker, NAN, NAN);

                return _vglyph_data_surface_add_point(points, matrix, &end_marker);
            }
            break;

        case VGLYPH_SEGMENT_MOVETO_ABS:
        case VGLYPH_SEGMENT_MOVETO_REL:
            state = _vglyph_data_surface_moveto(surface,
                                                (vglyph_segment_moveto_t*)segment,
                                                matrix,
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
            return _vglyph_data_surface_lineto(surface,
                                               (vglyph_segment_lineto_t*)segment,
                                               matrix,
                                               segment_type - VGLYPH_SEGMENT_LINETO_ABS,
                                               points,
                                               prev_point);

        case VGLYPH_SEGMENT_CURVETO_CUBIC_ABS:
        case VGLYPH_SEGMENT_CURVETO_CUBIC_REL:
            return _vglyph_data_surface_curveto_cubic(surface,
                                                      (vglyph_segment_curveto_cubic_t*)segment,
                                                      matrix,
                                                      segment_type - VGLYPH_SEGMENT_CURVETO_CUBIC_ABS,
                                                      points,
                                                      prev_point,
                                                      control_point);

        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS:
        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_REL:
            return _vglyph_data_surface_curveto_quadratic(surface,
                                                          (vglyph_segment_curveto_quadratic_t*)segment,
                                                          matrix,
                                                          segment_type - VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS,
                                                          points,
                                                          prev_point,
                                                          control_point);
            break;

        case VGLYPH_SEGMENT_ARC_ABS:
        case VGLYPH_SEGMENT_ARC_REL:
            return _vglyph_data_surface_arc(surface,
                                            (vglyph_segment_arc_t*)segment,
                                            matrix,
                                            segment_type - VGLYPH_SEGMENT_ARC_ABS,
                                            points,
                                            prev_point);

        case VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS:
        case VGLYPH_SEGMENT_LINETO_HORIZONTAL_REL:
            return _vglyph_data_surface_lineto_horizontal(surface,
                                                          (vglyph_segment_lineto_horizontal_t*)segment,
                                                          matrix,
                                                          segment_type - VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS,
                                                          points,
                                                          prev_point);

        case VGLYPH_SEGMENT_LINETO_VERTICAL_ABS:
        case VGLYPH_SEGMENT_LINETO_VERTICAL_REL:
            return _vglyph_data_surface_lineto_vertical(surface,
                                                        (vglyph_segment_lineto_vertical_t*)segment,
                                                        matrix,
                                                        segment_type - VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS,
                                                        points,
                                                        prev_point);

        case VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS:
        case VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_REL:
            return _vglyph_data_surface_curveto_cubic_smooth(surface,
                                                             (vglyph_segment_curveto_cubic_smooth_t*)segment,
                                                             matrix,
                                                             segment_type - VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS,
                                                             points,
                                                             prev_point,
                                                             control_point);

        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_ABS:
        case VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_REL:
            return _vglyph_data_surface_curveto_quadratic_smooth(surface,
                                                                 (vglyph_segment_curveto_quadratic_smooth_t*)segment,
                                                                 matrix,
                                                                 segment_type - VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_ABS,
                                                                 points,
                                                                 prev_point,
                                                                 control_point);
    }

    return state;
}

static vglyph_vector_t*
_vglyph_data_surface_figure_to_lines(vglyph_data_surface_t* surface,
                                     vglyph_figure_t* figure,
                                     const vglyph_matrix_t* matrix,
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

        *state = _vglyph_data_surface_segment_to_lines(surface, 
                                                       segment_type->segment, 
                                                       segment, 
                                                       matrix,
                                                       result, 
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
        *state = _vglyph_data_surface_segment_to_lines(surface, 
                                                       VGLYPH_SEGMENT_CLOSEPATH, 
                                                       &closepath, 
                                                       matrix,
                                                       result, 
                                                       &path_closed, 
                                                       &start_point, 
                                                       &prev_point,
                                                       &control_point);
    }

    return result;
}

static vglyph_vector_t**
_vglyph_data_surface_compute_intersections(vglyph_data_surface_t* surface,
                                           vglyph_vector_t* points,
                                           vglyph_state_t* state)
{
    *state = VGLYPH_STATE_SUCCESS;

    const vglyph_sint_t height = (vglyph_sint_t)(surface->base.height << surface->shift_mulitsampling);
    vglyph_vector_t** intersections = (vglyph_vector_t**)malloc(sizeof(vglyph_vector_t*) * height);

    if (!intersections)
    {
        *state = VGLYPH_STATE_OUT_OF_MEMORY;
        return NULL;
    }

    for (vglyph_sint_t y = 0; y < height; ++y)
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

        if (start_y < height && end_y >= 0)
        {
            if (start_y < 0)
                start_y = 0;

            if (end_y > height)
                end_y = height;

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
        }

        start = end;
    }

    return intersections;
}

static void 
_vglyph_data_surface_draw_polygon_without_multisampling(vglyph_data_surface_t* surface,
                                                        vglyph_vector_t** intersections,
                                                        const vglyph_color_t* color)
{
    vglyph_render_t* render = surface->base.render;

    void (*set_pixel)(vglyph_render_t*,
                      vglyph_surface_t*,
                      vglyph_sint32_t,
                      vglyph_sint32_t,
                      const vglyph_color_t*) = color->alpha < 1.0 ? 
        render->backend->alpha_blend : 
        render->backend->set_pixel;

    const vglyph_sint32_t width  = (vglyph_sint32_t)surface->base.width;
    const vglyph_sint32_t height = (vglyph_sint32_t)surface->base.height;
    const vglyph_uint_t offset_1 = sizeof(vglyph_float32_t);
    const vglyph_uint_t offset_2 = sizeof(vglyph_float32_t) << 1;

    vglyph_vector_t* currect_intersections;

    vglyph_float32_t s_x;
    vglyph_float32_t e_x;

    vglyph_sint32_t s_ix;
    vglyph_sint32_t e_ix;

    for (vglyph_sint32_t y = 0; y < height; ++y)
    { 
        currect_intersections = intersections[y];

        if (currect_intersections)
        {
            const vglyph_uint_t count_intersections = _vglyph_vector_size_in_bytes(currect_intersections);

            for (vglyph_uint_t i = 0; i < count_intersections; i += offset_2)
            {
                s_x = *(vglyph_float32_t*)_vglyph_vector_at(currect_intersections, i);
                e_x = *(vglyph_float32_t*)_vglyph_vector_at(currect_intersections, i + offset_1);

                s_ix = (vglyph_sint32_t)floorf(s_x);
                e_ix = (vglyph_sint32_t)ceilf(e_x);

                if (s_ix < 0)
                    s_ix = 0;
                else if (s_ix > width)
                    s_ix = width;

                if (e_ix < 0)
                    e_ix = 0;
                else if (e_ix > width)
                    e_ix = width;

                for (vglyph_sint32_t x = s_ix; x < e_ix; ++x)
                    set_pixel(render, &surface->base, x, y, color);
            }
        }
    }
}

static void 
_vglyph_data_surface_draw_polygon(vglyph_data_surface_t* surface,
                                  vglyph_vector_t** intersections,
                                  const vglyph_color_t* color)
{
    vglyph_render_t* render    = surface->base.render;
    vglyph_uint8_t*  data_back = surface->data_back;

    void (*set_pixel)(vglyph_render_t*,
                      vglyph_surface_t*,
                      vglyph_sint32_t,
                      vglyph_sint32_t,
                      const vglyph_color_t*) = color->alpha < 1.0 ? 
        render->backend->alpha_blend : 
        render->backend->set_pixel;

    const vglyph_sint32_t multisampling       = (vglyph_sint_t)surface->base.multisampling;
    const vglyph_uint_t   shift_mulitsampling = surface->shift_mulitsampling;

    const vglyph_sint32_t  width             = surface->base.width;
    const vglyph_sint32_t  height            = surface->base.height;
    const vglyph_sint32_t  rasterizer_width  = width  << shift_mulitsampling;
    const vglyph_sint32_t  rasterizer_height = height << shift_mulitsampling;
    const vglyph_uint_t    offset_1          = sizeof(vglyph_float32_t);
    const vglyph_uint_t    offset_2          = sizeof(vglyph_float32_t) << 1;
    const vglyph_uint_t    max_samples       = (vglyph_uint_t)(multisampling * multisampling);
    const vglyph_float64_t inv_max_samples   = 1.0 / max_samples;
    const vglyph_float64_t alpha             = color->alpha;

    vglyph_vector_t* currect_intersections;

    vglyph_float32_t s_x;
    vglyph_float32_t e_x;

    vglyph_sint32_t s_ix;
    vglyph_sint32_t e_ix;

    vglyph_sint32_t min_s_ix = INT32_MAX;
    vglyph_sint32_t max_e_ix = INT32_MIN;

    vglyph_sint32_t min_x;
    vglyph_sint32_t max_x;

    vglyph_color_t result_color = *color;

    for (vglyph_sint32_t y = 0; y < height; ++y)
    { 
        for (vglyph_sint32_t sample_y = 0; sample_y < multisampling; ++sample_y)
        {
            currect_intersections = intersections[(y << shift_mulitsampling) + sample_y];

            if (currect_intersections)
            {
                const vglyph_sint32_t offset_y = rasterizer_width * sample_y;
                const vglyph_uint_t count_intersections = _vglyph_vector_size_in_bytes(currect_intersections);

                for (vglyph_uint_t i = 0; i < count_intersections; i += offset_2)
                {
                    s_x = *(vglyph_float32_t*)_vglyph_vector_at(currect_intersections, i);
                    e_x = *(vglyph_float32_t*)_vglyph_vector_at(currect_intersections, i + offset_1);

                    s_ix = (vglyph_sint32_t)floorf(s_x);
                    e_ix = (vglyph_sint32_t)ceilf(e_x);

                    if (s_ix < 0)
                        s_ix = 0;
                    else if (s_ix > rasterizer_width)
                        s_ix = rasterizer_width;

                    if (e_ix < 0)
                        e_ix = 0;
                    else if (e_ix > rasterizer_width)
                        e_ix = rasterizer_width;

                    if (s_ix < min_s_ix)
                        min_s_ix = s_ix;

                    if (e_ix > max_e_ix)
                        max_e_ix = e_ix;

                    for (vglyph_sint32_t x = s_ix; x < e_ix; ++x)
                        data_back[x + offset_y] = 1;
                }
            }
        }

        if (min_s_ix != INT32_MAX)
        {
            min_x = (min_s_ix) >> shift_mulitsampling;
            max_x = (max_e_ix + multisampling - 1) >> shift_mulitsampling;

            for (vglyph_sint32_t x = min_x, offset_x = min_x << shift_mulitsampling
                 ; x < max_x
                 ; ++x, offset_x += multisampling)
            {
                vglyph_uint_t samples = 0;

                for (vglyph_sint_t sample_y = 0, offset_y = 0
                     ; sample_y < multisampling
                     ; ++sample_y, offset_y += rasterizer_width)
                {
                    for (vglyph_sint32_t mx = 0; mx < multisampling; ++mx)
                    {
                        samples += data_back[offset_x + mx + offset_y];
                        data_back[offset_x + mx + offset_y] = 0;
                    }
                }

                if (samples)
                {
                    result_color.alpha = alpha;

                    if (samples == max_samples)
                    {
                        set_pixel(render, &surface->base, x, y, &result_color);
                    }
                    else
                    {
                        result_color.alpha *= samples * inv_max_samples;
                        render->backend->alpha_blend(render, &surface->base, x, y, &result_color);
                    }
                }
            }

            min_s_ix = INT32_MAX;
            max_e_ix = INT32_MIN;
        }
    }
}

void
_vglyph_data_surface_init(vglyph_data_surface_t* surface,
                          const vglyph_object_backend_t* object_backend,
                          const vglyph_surface_backend_t* surface_backend,
                          vglyph_format_t* format,
                          vglyph_render_t* render,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height,
                          vglyph_uint32_t pitch,
                          vglyph_uint8_t* data)
{
    assert(data);

    _vglyph_surface_init(&surface->base, 
                         object_backend, 
                         surface_backend,
                         format, 
                         render,
                         width, 
                         height, 
                         pitch);

    surface->data      = data;
    surface->data_back = NULL;

    _vglyph_data_surface_update_multisampling(&surface->base);
}

void
_vglyph_data_surface_ctor(vglyph_data_surface_t* surface)
{
    _vglyph_surface_ctor(&surface->base);

    if (_vglyph_data_surface_is_valid(surface))
    {
    }
}

void
_vglyph_data_surface_dtor(vglyph_data_surface_t* surface)
{
    free(surface->data_back);

    _vglyph_surface_dtor(&surface->base);
}

vglyph_bool_t
_vglyph_data_surface_is_cast(vglyph_type_t* type)
{
    return _vglyph_data_surface_get_type() == type
        || _vglyph_surface_is_cast(type);
}

vglyph_type_t*
_vglyph_data_surface_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_data_surface_is_cast);
    return &type;
}

static void
_vglyph_data_surface_destroy(vglyph_object_t* object)
{
    vglyph_data_surface_t* surface = (vglyph_data_surface_t*)object;
    _vglyph_data_surface_dtor(surface);

    free(surface);
}

void 
_vglyph_data_surface_update_multisampling(vglyph_surface_t* surface)
{
    vglyph_multisampling_t multisampling = surface->multisampling;
    vglyph_data_surface_t* data_surface = (vglyph_data_surface_t*)surface;

    if (multisampling != VGLYPH_MULTISAMPLING_1)
    {
        vglyph_uint_t data_back_size =
            surface->width * multisampling * surface->multisampling;

        vglyph_uint8_t* data_back = (vglyph_uint8_t*)malloc(data_back_size);

        if (!data_back)
        {
            _vglyph_data_surface_set_state(data_surface, VGLYPH_STATE_OUT_OF_MEMORY);
            _vglyph_object_set_state_not_fatal(&data_surface->base.object);
            return;
        }

        memset(data_back, 0, data_back_size);
        free(data_surface->data_back);

        data_surface->data_back = data_back;
    }
    else
    {
        free(data_surface->data_back);
        data_surface->data_back = NULL;
    }

    vglyph_uint_t samples = multisampling;
    data_surface->shift_mulitsampling = 0;

    while (samples >>= 1)
        ++data_surface->shift_mulitsampling;
}

vglyph_uint8_t*
_vglyph_data_surface_lock(vglyph_surface_t* surface,
                          vglyph_uint32_t x,
                          vglyph_uint32_t y,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height)
{
    return ((vglyph_data_surface_t*)surface)->data;
}

void
_vglyph_data_surface_unlock(vglyph_surface_t* surface)
{
}

void
_vglyph_data_surface_fill(vglyph_surface_t* surface,
                          vglyph_uint32_t x,
                          vglyph_uint32_t y,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height,
                          const vglyph_color_t* color)
{
    vglyph_render_t* render = surface->render;
    render->backend->fill(render, surface, x, y, width, height, color);
}

void
_vglyph_data_surface_get_pixel(vglyph_surface_t* surface,
                               vglyph_sint32_t x,
                               vglyph_sint32_t y,
                               vglyph_color_t* color)
{
    vglyph_render_t* render = surface->render;
    render->backend->get_pixel(render, surface, x, y, color);
}

void
_vglyph_data_surface_set_pixel(vglyph_surface_t* surface,
                               vglyph_sint32_t x,
                               vglyph_sint32_t y,
                               const vglyph_color_t* color)
{
    vglyph_render_t* render = surface->render;
    render->backend->set_pixel(render, surface, x, y, color);
}

vglyph_bool_t
_vglyph_data_surface_draw_glyph(vglyph_surface_t* surface,
                                vglyph_glyph_t* glyph,
                                const vglyph_color_t* color,
                                const vglyph_point_t* position,
                                const vglyph_point_t* origin,
                                vglyph_float32_t angle)
{
    const vglyph_float32_t pi = 3.14159265358979323846f;
    const vglyph_float32_t degree_to_radians = pi / 180.0f;

    const vglyph_sint_t multisampling = 
        (vglyph_sint_t)(((vglyph_data_surface_t*)surface)->base.multisampling);

    const vglyph_float32_t width  = (vglyph_float32_t)(surface->width  * multisampling);
    const vglyph_float32_t height = (vglyph_float32_t)(surface->height * multisampling);

    vglyph_matrix_t mat;
    _vglyph_matrix_identity(&mat);

    //if (origin)
    //    _vglyph_matrix_translate(&mat, &mat, origin->x, origin->y);

    _vglyph_matrix_translate(&mat, &mat, 0.0f, height);
    _vglyph_matrix_scale(&mat, &mat, 1.0f, -1.0f);

    if (angle != 0.0f)
        _vglyph_matrix_rotate(&mat, &mat, angle * degree_to_radians);

    _vglyph_matrix_translate(&mat, &mat, -glyph->bearing_x * width, -glyph->bearing_y * height);

    //if (position)
    //    _vglyph_matrix_translate(&mat, &mat, position->x, position->y);

    vglyph_data_surface_t* data_surface = (vglyph_data_surface_t*)surface;

    vglyph_state_t    state         = VGLYPH_STATE_SUCCESS;
    vglyph_vector_t*  points        = NULL;
    vglyph_vector_t** intersections = NULL;

    do
    {
        points = _vglyph_data_surface_figure_to_lines(data_surface, glyph->figure, &mat, &state);

        if (state != VGLYPH_STATE_SUCCESS)
            break;

        intersections = _vglyph_data_surface_compute_intersections(data_surface, points, &state);
        
        if (state != VGLYPH_STATE_SUCCESS)
            break;

        _vglyph_vector_destroy(points);
        points = NULL;

        if (data_surface->base.multisampling == VGLYPH_MULTISAMPLING_1)
            _vglyph_data_surface_draw_polygon_without_multisampling(data_surface, intersections, color);
        else
            _vglyph_data_surface_draw_polygon(data_surface, intersections, color);

    } while (FALSE);

    if (points)
        _vglyph_vector_destroy(points);

    if (intersections)
    {
        const vglyph_uint32_t height = 
            surface->height << data_surface->shift_mulitsampling;

        for (vglyph_uint32_t y = 0; y < height; ++y)
        {
            if (intersections[y])
                _vglyph_vector_destroy(intersections[y]);
        }

        free(intersections);
    }

    if (state != VGLYPH_STATE_SUCCESS)
    {
        _vglyph_data_surface_set_state(data_surface, state);
        _vglyph_object_set_state_not_fatal(&data_surface->base.object);

        return FALSE;
    }

    return TRUE;
}

static const vglyph_object_backend_t vglyph_data_surface_object_backend = {
    _vglyph_data_surface_get_type,
    _vglyph_data_surface_is_cast,
    _vglyph_data_surface_destroy
};

const vglyph_surface_backend_t vglyph_data_surface_backend = {
    _vglyph_data_surface_update_multisampling,
    _vglyph_data_surface_lock,
    _vglyph_data_surface_unlock,
    _vglyph_data_surface_fill,
    _vglyph_data_surface_get_pixel,
    _vglyph_data_surface_set_pixel,
    _vglyph_data_surface_draw_glyph
};

vglyph_uint32_t
_vglyph_data_surface_get_pitch(vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_alignment_t row_alignment)
{
    assert(format);
    assert(row_alignment == VGLYPH_ALIGNMENT_1 ||
           row_alignment == VGLYPH_ALIGNMENT_2 ||
           row_alignment == VGLYPH_ALIGNMENT_4 ||
           row_alignment == VGLYPH_ALIGNMENT_8);

    vglyph_uint32_t bits_per_pixel = vglyph_format_get_bits_per_pixel(format);
    vglyph_uint32_t pitch = (width * bits_per_pixel + 7) >> 3;
    vglyph_uint32_t align = row_alignment - 1;
    pitch = (pitch + align) & ~align;

    return pitch;
}

vglyph_render_t*
_vglyph_data_surface_create_render(vglyph_format_t* format)
{
    if (vglyph_object_is_cast(&format->object, vglyph_get_rgba_uint_format_type()))
    {
        vglyph_rgba_uint_format_t* rgba_uint_format = (vglyph_rgba_uint_format_t*)format;

        if (rgba_uint_format->bit_count.r +
            rgba_uint_format->bit_count.g +
            rgba_uint_format->bit_count.b +
            rgba_uint_format->bit_count.a == 32)
            return _vglyph_rgba_uint32_data_render_create(rgba_uint_format);

        if (rgba_uint_format->bit_count.r +
            rgba_uint_format->bit_count.g +
            rgba_uint_format->bit_count.b +
            rgba_uint_format->bit_count.a == 16)
            return _vglyph_rgba_uint16_data_render_create(rgba_uint_format);

        if ((rgba_uint_format->base.packaging_bytes.endianness == VGLYPH_ENDIANNESS_HOST && _vglyph_is_little_endian()) ||
            rgba_uint_format->base.packaging_bytes.endianness == VGLYPH_ENDIANNESS_LITTLE)
            return _vglyph_rgba_little_uint_data_render_create();

        return _vglyph_rgba_uint_data_render_create();
    }

    return (vglyph_render_t*)_vglyph_object_invalid_format();
}

vglyph_uint32_t
vglyph_surface_get_data_size(vglyph_format_t* format,
                             vglyph_uint32_t width,
                             vglyph_uint32_t height,
                             vglyph_alignment_t row_alignment)
{
    vglyph_uint32_t pitch =
        _vglyph_data_surface_get_pitch(format, width, height, row_alignment);

    return pitch * height;
}

vglyph_surface_t*
vglyph_surface_create_for_data(vglyph_uint8_t* data,
                               vglyph_uint32_t data_size,
                               vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_alignment_t row_alignment)
{
    assert(data);
    assert(format);
    assert(data_size >= vglyph_surface_get_data_size(format, width, height, row_alignment));

    vglyph_data_surface_t* surface = (vglyph_data_surface_t*)malloc(sizeof(vglyph_data_surface_t));

    if (!surface)
        return (vglyph_surface_t*)_vglyph_object_out_of_memory();

    vglyph_uint32_t pitch =
        _vglyph_data_surface_get_pitch(format, width, height, row_alignment);

    vglyph_render_t* render = _vglyph_data_surface_create_render(format);

    _vglyph_data_surface_init(surface,
                              &vglyph_data_surface_object_backend,
                              &vglyph_data_surface_backend, 
                              format,
                              render,
                              width,
                              height,
                              pitch,
                              data);

    _vglyph_render_destroy(render);

    _vglyph_data_surface_ctor(surface);

    return &surface->base;
}
