/* vglyph-test - test library for visualize glyphs
 *
 * File: bitmap.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef BITMAP_H
#define BITMAP_H

#include "vglyph.h"

vglyph_bool_t
bitmap_save(vglyph_surface_t* surface, 
            const char* name);

#endif
