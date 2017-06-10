/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-format.h"

static vglyph_uuid_t vglyph_format_type = {
    0x6c49fb82, 0xbc98, 0x4b2a, 0xb0, 0x89, { 0xa6, 0xb1, 0x0a, 0xac, 0x2e, 0xad }
};

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
_vglyph_format_is_cast(vglyph_uuid_t* uuid)
{
    return _vglyph_uuid_equal(uuid, &vglyph_format_type);
}

static void
_vglyph_format_destroy(vglyph_object_t* object)
{
    vglyph_format_t* format = (vglyph_format_t*)object;
    _vglyph_format_dtor(format);

    free(format);
}

static const vglyph_object_backend_t vglyph_format_object_backend = {
    _vglyph_format_is_cast,
    _vglyph_format_destroy
};

vglyph_object_t*
vglyph_format_to_object(vglyph_format_t* format)
{
    assert(format);
    return &format->object;
}

vglyph_format_t*
vglyph_object_to_format(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_format_t*)_vglyph_object_to_type(object, &vglyph_format_type);
}
