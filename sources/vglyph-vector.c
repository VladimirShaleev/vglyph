/* vglyph - library for visualize glyphs
 *
 * File: vglyph-vector.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-vector.h"
#include "vglyph-type.h"

vglyph_type_t*
_vglyph_vector_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(&_vglyph_vector_object_backend);
    return &type;
}

static vglyph_type_t*
_vglyph_vector_get_type_callback(void)
{
    return _vglyph_vector_get_type();
}

static vglyph_bool_t
_vglyph_vector_is_cast_callback(vglyph_type_t* type)
{
    return _vglyph_vector_get_type() == type;
}

static void
_vglyph_vector_destroy_callback(vglyph_object_t* object)
{
    vglyph_vector_t* vector = (vglyph_vector_t*)object;
    _vglyph_vector_dtor(vector);

    free(vector);
}

const vglyph_object_backend_t _vglyph_vector_object_backend = {
    _vglyph_vector_get_type_callback,
    _vglyph_vector_is_cast_callback,
    _vglyph_vector_destroy_callback
};
