/* vglyph - library for visualize glyphs
 *
 * File: vglyph-face.h
 * Copyright (C) 2019 Shaleev Vladimir
 */

#ifndef VGLYPH_FACE_H
#define VGLYPH_FACE_H

#include "vglyph-object.h"

struct _vglyph_face
{
    vglyph_object_t object;
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

#endif
