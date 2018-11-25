/* vglyph - library for visualize glyphs
 *
 * File: vglyph-transform.h
 * Copyright (C) 2018 Shaleev Vladimir
 */

#ifndef VGLYPH_TRANSFORM_H
#define VGLYPH_TRANSFORM_H

#include "vglyph-object.h"
#include "vglyph-matrix.h"

struct _vglyph_transform
{
    vglyph_object_t object;
    vglyph_matrix_t matrix;
};

static inline vglyph_transform_t*
_vglyph_transform_reference(vglyph_transform_t* transform)
{
    assert(transform);
    return (vglyph_transform_t*)_vglyph_object_reference(&transform->object);
}

static inline void
_vglyph_transform_destroy(vglyph_transform_t* transform)
{
    assert(transform);
    _vglyph_object_destroy(&transform->object);
}

static inline int
_vglyph_transform_get_reference_count(vglyph_transform_t* transform)
{
    assert(transform);
    return _vglyph_object_get_reference_count(&transform->object);
}

static inline vglyph_state_t
_vglyph_transform_get_state(vglyph_transform_t* transform)
{
    assert(transform);
    return _vglyph_object_get_state(&transform->object);
}

static inline void
_vglyph_transform_set_state(vglyph_transform_t* transform,
                            vglyph_state_t state)
{
    assert(transform);
    _vglyph_object_set_state(&transform->object, state);
}

static inline vglyph_bool_t
_vglyph_transform_is_valid(vglyph_transform_t* transform)
{
    assert(transform);
    return _vglyph_object_is_valid(&transform->object);
}

#endif
