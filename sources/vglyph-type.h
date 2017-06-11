/* vglyph - library for visualize glyphs
 *
 * File: vglyph-type.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_TYPE_H
#define VGLYPH_TYPE_H

#include "vglyph-object.h"

extern const vglyph_object_backend_t _vglyph_type_object_backend;

struct _vglyph_type
{
    vglyph_object_t object;
    vglyph_bool_t (*is_cast)(vglyph_type_t* type);
};

static inline vglyph_bool_t
_vglyph_type_is_valid(vglyph_type_t* type)
{
    assert(type);
    return _vglyph_object_is_valid(&type->object);
}

#define _vglyph_type_create(_is_cast) \
{                                     \
    { VGLYPH_REFERENCE_COUNT_INVALID, \
      VGLYPH_STATE_SUCCESS,           \
      &_vglyph_type_object_backend }, \
    _is_cast                          \
};

#endif
