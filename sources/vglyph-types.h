/* vglyph - library for visualize glyphs
 *
 * File: vglyph-types.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_TYPES_H
#define VGLYPH_TYPES_H

#ifndef FALSE
# define FALSE 0
#endif

#ifndef TRUE
# define TRUE 1
#endif

typedef intptr_t  vglyph_sint_t;
typedef uintptr_t vglyph_uint_t;
typedef int8_t    vglyph_sint8_t;
typedef uint8_t   vglyph_uint8_t;

typedef enum _vglyph_type
{
    VGLYPH_TYPE_OBJECT  = 0,
    VGLYPH_TYPE_VECTOR  = 1,
    VGLYPH_TYPE_FIGURE  = 2,
    VGLYPH_TYPE_SURFACE = 3
} vglyph_type_t;

#endif
