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

vglyph_object_t*
_vglyph_object_invalid_cast()
{
    static vglyph_object_t vglyph_object_invalid_cast = {
        VGLYPH_REFERENCE_COUNT_INVALID,
        VGLYPH_STATE_INVALID_CAST
    };

    return &vglyph_object_invalid_cast;
}

vglyph_object_t*
_vglyph_object_to_type(vglyph_object_t* object,
                       vglyph_uuid_t* uuid)
{
    static vglyph_uuid_t type = { 
        0x8690b4de, 0xb6de, 0x4762, 0xa6, 0xfa, { 0x6c, 0xbf, 0xd3, 0x60, 0xf4, 0x0e }
    };

    if (_vglyph_object_is_valid(object))
    {
        if (object->is_cast_func(uuid) || _vglyph_uuid_equal(uuid, &type))
            return _vglyph_object_reference(object);
    }

    return _vglyph_object_invalid_cast();
}

vglyph_object_t*
vglyph_object_reference(vglyph_object_t* object)
{
    assert(object);
    return _vglyph_object_reference(object);
}

void
vglyph_object_destroy(vglyph_object_t* object)
{
    assert(object);
    _vglyph_object_destroy(object);
}

int
vglyph_object_get_reference_count(vglyph_object_t* object)
{
    assert(object);
    return _vglyph_object_get_reference_count(object);
}

vglyph_state_t
vglyph_object_get_state(vglyph_object_t* object)
{
    assert(object);
    return _vglyph_object_get_state(object);
}
