/* vglyph - library for visualize glyphs
 *
 * File: vglyph-object.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-object.h"
#include "vglyph-type.h"

vglyph_object_t*
_vglyph_object_out_of_memory(void)
{
    static vglyph_object_t vglyph_object_out_of_memory = {
        VGLYPH_REFERENCE_COUNT_INVALID,
        VGLYPH_STATE_OUT_OF_MEMORY
    };

    return &vglyph_object_out_of_memory;
}

vglyph_object_t*
_vglyph_object_invalid_cast(void)
{
    static vglyph_object_t vglyph_object_invalid_cast = {
        VGLYPH_REFERENCE_COUNT_INVALID,
        VGLYPH_STATE_INVALID_CAST
    };

    return &vglyph_object_invalid_cast;
}

vglyph_object_t*
_vglyph_object_invalid_format(void)
{
    static vglyph_object_t vglyph_object_invalid_format = {
        VGLYPH_REFERENCE_COUNT_INVALID,
        VGLYPH_STATE_INVALID_FORMAT
    };

    return &vglyph_object_invalid_format;
}

vglyph_object_t*
_vglyph_object_to_type(vglyph_object_t* object,
                       vglyph_type_t* type)
{
    if (vglyph_object_is_cast(object, type))
        return object;

    return _vglyph_object_invalid_cast();
}

vglyph_type_t*
vglyph_get_object_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(NULL);
    return &type;
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

vglyph_sint32_t
vglyph_object_get_reference_count(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_sint32_t)_vglyph_object_get_reference_count(object);
}

vglyph_state_t
vglyph_object_get_state(vglyph_object_t* object)
{
    assert(object);
    return _vglyph_object_get_state(object);
}

vglyph_type_t*
vglyph_object_get_type(vglyph_object_t* object)
{
    assert(object);
    return _vglyph_object_get_type(object);
}

vglyph_bool_t
vglyph_object_is_cast(vglyph_object_t* object,
                      vglyph_type_t* type)
{
    assert(object);

    if (_vglyph_object_is_valid(object))
    {
        if (object->backend->is_cast(type) || vglyph_get_object_type() == type)
            return TRUE;
    }

    return FALSE;
}
