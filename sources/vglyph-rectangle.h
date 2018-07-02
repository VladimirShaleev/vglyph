/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rectangle.h
 * Copyright (C) 2018 Shaleev Vladimir
 */

#ifndef VGLYPH_RECTANGLE_H
#define VGLYPH_RECTANGLE_H

#include "vglyph-api.h"
#include "vglyph-point.h"

typedef struct _vglyph_rectangle
{
    vglyph_float32_t left;
    vglyph_float32_t top;
    vglyph_float32_t right;
    vglyph_float32_t bottom;
} vglyph_rectangle_t;

static inline vglyph_rectangle_t*
_vglyph_rectangle_init(vglyph_rectangle_t* result,
                       vglyph_float32_t left,
                       vglyph_float32_t top,
                       vglyph_float32_t right,
                       vglyph_float32_t bottom)
{
    assert(result);

    result->left   = left;
    result->top    = top;
    result->right  = right;
    result->bottom = bottom;

    return result;
}

static inline vglyph_rectangle_t*
_vglyph_rectangle_init_from_points(vglyph_rectangle_t* result,
                                   const vglyph_point_t* point1,
                                   const vglyph_point_t* point2)
{
    assert(result);
    assert(point1);
    assert(point2);

    if (point1->x < point2->x)
    {
        result->left  = point1->x;
        result->right = point2->x;
    }
    else
    {
        result->left  = point2->x;
        result->right = point1->x;
    }

    if (point1->y < point2->y)
    {
        result->top    = point1->y;
        result->bottom = point2->y;
    }
    else
    {
        result->top    = point2->y;
        result->bottom = point1->y;
    }

    return result;
}

static inline vglyph_rectangle_t*
_vglyph_rectangle_add_point(vglyph_rectangle_t* result,
                            const vglyph_rectangle_t* rectangle,
                            const vglyph_point_t* point)
{
    assert(result);
    assert(rectangle);
    assert(point);

    if (point->x < rectangle->left)
    {
        result->left  = point->x;
        result->right = rectangle->right;
    }
    else if (point->x > rectangle->right)
    {
        result->left  = rectangle->left;
        result->right = point->x;
    }

    if (point->y < rectangle->top)
    {
        result->top    = point->y;
        result->bottom = rectangle->bottom;
    }
    else if (point->y > rectangle->bottom)
    {
        result->top    = rectangle->top;
        result->bottom = point->y;
    }

    return result;
}

#endif
