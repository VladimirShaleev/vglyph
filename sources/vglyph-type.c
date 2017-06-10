/* vglyph - library for visualize glyphs
 *
 * File: vglyph-type.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-type.h"

static vglyph_type_t*
_vglyph_type_get_type(void)
{
    return vglyph_get_type_type();
}

static vglyph_bool_t
_vglyph_type_is_cast(vglyph_type_t* type)
{
    return _vglyph_type_get_type() == type;
}

const vglyph_object_backend_t _vglyph_type_object_backend = {
    _vglyph_type_get_type,
    _vglyph_type_is_cast,
    NULL
};

vglyph_type_t*
vglyph_get_type_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(&_vglyph_type_object_backend);
    return &type;
}

vglyph_type_t*
vglyph_object_to_type(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_type_t*)_vglyph_object_to_type(object, _vglyph_type_get_type());
}

vglyph_object_t*
vglyph_type_to_object(vglyph_type_t* type)
{
    assert(type);
    return &type->object;
}

vglyph_bool_t
vglyph_type_is_type(vglyph_type_t* type,
                    vglyph_type_t* equal_type)
{
    assert(type);
    assert(equal_type);

    if (_vglyph_type_is_valid(type) && _vglyph_type_is_valid(equal_type))
    {
        if (type->backend && type->backend->is_cast(equal_type))
            return TRUE;

        if (vglyph_get_object_type() == equal_type)
            return TRUE;
    }

    return FALSE;
}
