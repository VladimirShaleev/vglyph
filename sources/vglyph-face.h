/* vglyph - library for visualize glyphs
 *
 * File: vglyph-face.h
 * Copyright (C) 2019 Shaleev Vladimir
 */

#ifndef VGLYPH_FACE_H
#define VGLYPH_FACE_H

#include "vglyph-object.h"
#include "vglyph-vector.h"
#include "vglyph-glyph.h"

typedef struct _vglyph_charmap
{
    vglyph_glyph_t* glyph;
    vglyph_uint32_t char_code;
} vglyph_charmap_t;

struct _vglyph_face
{
    vglyph_object_t  object;
    vglyph_vector_t* charmap;
};

static inline vglyph_face_t*
_vglyph_face_reference(vglyph_face_t* face)
{
    assert(face);
    return (vglyph_face_t*)_vglyph_object_reference(&face->object);
}

static inline void
_vglyph_face_destroy(vglyph_face_t* face)
{
    assert(face);
    _vglyph_object_destroy(&face->object);
}

static inline int
_vglyph_face_get_reference_count(vglyph_face_t* face)
{
    assert(face);
    return _vglyph_object_get_reference_count(&face->object);
}

static inline vglyph_state_t
_vglyph_face_get_state(vglyph_face_t* face)
{
    assert(face);
    return _vglyph_object_get_state(&face->object);
}

static inline void
_vglyph_face_set_state(vglyph_face_t* face,
                       vglyph_state_t state)
{
    assert(face);
    _vglyph_object_set_state(&face->object, state);
}

static inline vglyph_bool_t
_vglyph_face_is_valid(vglyph_face_t* face)
{
    assert(face);
    return _vglyph_object_is_valid(&face->object);
}

static inline vglyph_glyph_t*
_vglyph_face_find_glyph(vglyph_face_t* face,
                        vglyph_uint32_t char_code,
                        vglyph_uint_t* offset)
{
    vglyph_vector_t*  charmap = face->charmap;
    vglyph_charmap_t* current;

    vglyph_sint64_t left  = -1;
    vglyph_sint64_t right = (vglyph_sint64_t)_vglyph_vector_size_in_bytes(charmap) / sizeof(vglyph_charmap_t);
    vglyph_sint64_t middle;
    vglyph_uint_t   find_offset;

    while (left < right - 1)
    {
        middle      = (left + right) >> 1;
        find_offset = (vglyph_uint_t)middle * sizeof(vglyph_charmap_t);

        current = (vglyph_charmap_t*)_vglyph_vector_at(charmap, find_offset);

        if (current->char_code == char_code)
        {
            if (offset)
                *offset = find_offset;

            return current->glyph;
        }

        if (current->char_code < char_code)
            left = middle;
        else
            right = middle;
    }

    return NULL;
}

#endif
