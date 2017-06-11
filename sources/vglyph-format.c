/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-format.h"
#include "vglyph-type.h"

void
_vglyph_format_init(vglyph_format_t* format,
                    const vglyph_object_backend_t* object_backend)
{
    _vglyph_object_init(&format->object, object_backend);
}

void
_vglyph_format_ctor(vglyph_format_t* format)
{
}

void
_vglyph_format_dtor(vglyph_format_t* format)
{
}

vglyph_bool_t
_vglyph_format_is_cast(vglyph_type_t* type)
{
    return vglyph_get_format_type() == type;
}

static void
_vglyph_format_destroy(vglyph_object_t* object)
{
    vglyph_format_t* format = (vglyph_format_t*)object;
    _vglyph_format_dtor(format);

    free(format);
}

static const vglyph_object_backend_t vglyph_format_object_backend = {
    vglyph_get_format_type,
    _vglyph_format_is_cast,
    _vglyph_format_destroy
};

vglyph_type_t*
vglyph_get_format_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_format_is_cast);
    return &type;
}

vglyph_format_t*
vglyph_object_to_format(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_format_t*)_vglyph_object_to_type(object, vglyph_get_format_type());
}

vglyph_object_t*
vglyph_format_to_object(vglyph_format_t* format)
{
    assert(format);
    return &format->object;
}
