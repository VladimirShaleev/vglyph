/* vglyph - library for visualize glyphs
 *
 * File: vglyph-figure.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_FIGURE_H
#define VGLYPH_FIGURE_H

#include "vglyph-object.h"

struct _vglyph_figure
{
    vglyph_object_t object;
};

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

#endif
