/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment-close-path.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_SEGMENT_CLOSE_PATH_H
#define VGLYPH_SEGMENT_CLOSE_PATH_H

#include "vglyph-segment.h"

typedef struct
{
    vglyph_segment_t base;
} vglyph_segment_close_path_t;

static inline void
_vglyph_segment_close_path_set_state(vglyph_segment_close_path_t* segment_close_path,
                                     vglyph_state_t state)
{
    assert(segment_close_path);
    _vglyph_segment_set_state(&segment_close_path->base, state);
}

static inline vglyph_bool_t
_vglyph_segment_close_path_is_valid(vglyph_segment_close_path_t* segment_close_path)
{
    assert(segment_close_path);
    return _vglyph_segment_is_valid(&segment_close_path->base);
}

#endif
