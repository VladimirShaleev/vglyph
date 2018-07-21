/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment-types.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_SEGMENT_TYPES_H
#define VGLYPH_SEGMENT_TYPES_H

#include "vglyph-api.h"
#include "vglyph-types.h"

typedef enum _vglyph_segment
{
    VGLYPH_SEGMENT_UNKNOWN                      = 0,
    VGLYPH_SEGMENT_CLOSEPATH                    = 1,
    VGLYPH_SEGMENT_MOVETO_ABS                   = 2,
    VGLYPH_SEGMENT_MOVETO_REL                   = 3,
    VGLYPH_SEGMENT_LINETO_ABS                   = 4,
    VGLYPH_SEGMENT_LINETO_REL                   = 5,
    VGLYPH_SEGMENT_CURVETO_CUBIC_ABS            = 6,
    VGLYPH_SEGMENT_CURVETO_CUBIC_REL            = 7,
    VGLYPH_SEGMENT_CURVETO_QUADRATIC_ABS        = 8,
    VGLYPH_SEGMENT_CURVETO_QUADRATIC_REL        = 9,
    VGLYPH_SEGMENT_ARC_ABS                      = 10,
    VGLYPH_SEGMENT_ARC_REL                      = 11,
    VGLYPH_SEGMENT_LINETO_HORIZONTAL_ABS        = 12,
    VGLYPH_SEGMENT_LINETO_HORIZONTAL_REL        = 13,
    VGLYPH_SEGMENT_LINETO_VERTICAL_ABS          = 14,
    VGLYPH_SEGMENT_LINETO_VERTICAL_REL          = 15,
    VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_ABS     = 16,
    VGLYPH_SEGMENT_CURVETO_CUBIC_SMOOTH_REL     = 17,
    VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_ABS = 18,
    VGLYPH_SEGMENT_CURVETO_QUADRATIC_SMOOTH_REL = 19
} vglyph_segment_t;

typedef struct _vglyph_segment_closepath
{
    vglyph_uint_t unused;
} vglyph_segment_closepath_t;

typedef struct _vglyph_segment_moveto
{
    vglyph_point_t point;
} vglyph_segment_moveto_t;

typedef struct _vglyph_segment_lineto
{
    vglyph_point_t point;
} vglyph_segment_lineto_t;

typedef struct _vglyph_segment_curveto_cubic
{
    vglyph_point_t point;
    vglyph_point_t point1;
    vglyph_point_t point2;
} vglyph_segment_curveto_cubic_t;

typedef struct _vglyph_segment_curveto_quadratic
{
    vglyph_point_t point;
    vglyph_point_t point1;
} vglyph_segment_curveto_quadratic_t;

typedef struct _vglyph_segment_arc
{
    vglyph_point_t   point; 
    vglyph_point_t   radius;
    vglyph_float32_t angle;
    vglyph_bool_t    large_arc_flag;
    vglyph_bool_t    sweep_flag;
} vglyph_segment_arc_t;

typedef struct _vglyph_segment_lineto_horizontal
{
    vglyph_float32_t x;
} vglyph_segment_lineto_horizontal_t;

typedef struct _vglyph_segment_lineto_vertical
{
    vglyph_float32_t y;
} vglyph_segment_lineto_vertical_t;

typedef struct _vglyph_segment_curveto_cubic_smooth
{
    vglyph_point_t point;
    vglyph_point_t point2;
} vglyph_segment_curveto_cubic_smooth_t;

typedef struct _vglyph_segment_curveto_quadratic_smooth
{
    vglyph_point_t point;
} vglyph_segment_curveto_quadratic_smooth_t;

#endif
