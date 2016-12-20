/* vglyph - library for visualize glyphs
 *
 * File: vglyph-vector.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-vector.h"

vglyph_uuid_t _vglyph_vector_type = {
    0x018f0c8d, 0xb600, 0x4bcb, 0xb6, 0xce,{ 0xfc, 0xf6, 0x31, 0xfd, 0xfe, 0x2b }
};

static vglyph_bool_t
_vglyph_vector_is_cast_callback(vglyph_uuid_t* uuid)
{
    return _vglyph_uuid_equal(uuid, &_vglyph_vector_type);
}

static void
_vglyph_vector_destroy_callback(vglyph_object_t* object)
{
    vglyph_vector_t* vector = (vglyph_vector_t*)object;
    _vglyph_vector_dtor(vector);

    free(vector);
}

const vglyph_object_backend_t _vglyph_vector_object_backend = {
    _vglyph_vector_is_cast_callback,
    _vglyph_vector_destroy_callback
};
