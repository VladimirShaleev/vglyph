/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format-parser.h
 * Copyright (C) 2019 Shaleev Vladimir
 */

#ifndef VGLYPH_FORMAT_PARSER_H
#define VGLYPH_FORMAT_PARSER_H

#include "vglyph-api.h"

typedef enum _vglyph_format_type
{
    VGLYPH_FORMAT_TYPE_UNKNOWN = 0,
    VGLYPH_FORMAT_TYPE_UINT    = 1,
    VGLYPH_FORMAT_TYPE_FLOAT   = 2
} vglyph_format_type_t;

vglyph_format_type_t
_vglyph_format_parse(const char* format,
                     vglyph_rgba_components_t* components,
                     vglyph_sint_t channels[4],
                     vglyph_uint_t* byte_count);

#endif
