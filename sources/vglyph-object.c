/* vglyph - library for visualize glyphs
 *
 * File: vglyph-object.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-object.h"

vglyph_object_t*
_vglyph_object_out_of_memory()
{
    static vglyph_object_t vglyph_object_out_of_memory = {
        VGLYPH_REFERENCE_COUNT_INVALID,
        VGLYPH_STATE_OUT_OF_MEMORY
    };

    return &vglyph_object_out_of_memory;
}
