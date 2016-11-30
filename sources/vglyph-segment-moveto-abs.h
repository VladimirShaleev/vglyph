/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment-moveto-abs.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_SEGMENT_MOVETO_ABS_H
#define VGLYPH_SEGMENT_MOVETO_ABS_H

#include "vglyph-segment.h"

typedef struct
{
    vglyph_segment_t base;
    vglyph_point_t   point;
} vglyph_segment_moveto_abs_t;

static inline void
_vglyph_segment_moveto_abs_set_state(vglyph_segment_moveto_abs_t* segment_moveto_abs,
                                     vglyph_state_t state)
{
    assert(segment_moveto_abs);
    _vglyph_segment_set_state(&segment_moveto_abs->base, state);
}

static inline vglyph_bool_t
_vglyph_segment_moveto_abs_is_valid(vglyph_segment_moveto_abs_t* segment_moveto_abs)
{
    assert(segment_moveto_abs);
    return _vglyph_segment_is_valid(&segment_moveto_abs->base);
}

#endif
