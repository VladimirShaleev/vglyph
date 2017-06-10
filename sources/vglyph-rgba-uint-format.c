﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint-format.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-rgba-uint-format.h"
#include "vglyph-type.h"

void
_vglyph_rgba_uint_format_init(vglyph_rgba_uint_format_t* format,
                              const vglyph_object_backend_t* object_backend,
                              const vglyph_rgba_components_t* components,
                              const vglyph_rgba_uint_bit_count_t* bit_count)
{
    _vglyph_format_init(&format->base, object_backend);

    format->components = *components;
    format->bit_count  = *bit_count;
}

void
_vglyph_rgba_uint_format_ctor(vglyph_rgba_uint_format_t* format)
{
    _vglyph_format_ctor(&format->base);

    if (_vglyph_rgba_uint_format_is_valid(format))
    {
    }
}

void
_vglyph_rgba_uint_format_dtor(vglyph_rgba_uint_format_t* format)
{
    _vglyph_format_dtor(&format->base);
}

vglyph_bool_t
_vglyph_rgba_uint_format_is_cast(vglyph_type_t* type)
{
    return vglyph_get_rgba_uint_format_type() == type
        || _vglyph_format_is_cast(type);
}

static void
_vglyph_rgba_uint_format_destroy(vglyph_object_t* object)
{
    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)object;
    _vglyph_rgba_uint_format_dtor(format);

    free(format);
}

static const vglyph_object_backend_t vglyph_rgba_uint_format_object_backend = {
    vglyph_get_rgba_uint_format_type,
    _vglyph_rgba_uint_format_is_cast,
    _vglyph_rgba_uint_format_destroy
};

vglyph_type_t*
vglyph_get_rgba_uint_format_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(&vglyph_rgba_uint_format_object_backend);
    return &type;
}

vglyph_rgba_uint_format_t*
vglyph_object_to_rgba_uint_format(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_rgba_uint_format_t*)_vglyph_object_to_type(object, vglyph_get_rgba_uint_format_type());
}

vglyph_rgba_uint_format_t*
vglyph_format_to_rgba_uint_format(vglyph_format_t* format)
{
    assert(format);
    return (vglyph_rgba_uint_format_t*)_vglyph_object_to_type(&format->object, vglyph_get_rgba_uint_format_type());
}

vglyph_rgba_uint_format_t*
vglyph_rgba_uint_format_create(const vglyph_rgba_components_t* components,
                               const vglyph_rgba_uint_bit_count_t* bit_count)
{
    assert(components);
    assert(bit_count);
    assert(components->r >= VGLYPH_COMPONENT_ZERO && components->r <= VGLYPH_COMPONENT_ALPHA);
    assert(components->g >= VGLYPH_COMPONENT_ZERO && components->g <= VGLYPH_COMPONENT_ALPHA);
    assert(components->b >= VGLYPH_COMPONENT_ZERO && components->b <= VGLYPH_COMPONENT_ALPHA);
    assert(components->a >= VGLYPH_COMPONENT_ZERO && components->a <= VGLYPH_COMPONENT_ALPHA);

    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)malloc(sizeof(vglyph_rgba_uint_format_t));

    if (!format)
        return (vglyph_rgba_uint_format_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_uint_format_init(format, &vglyph_rgba_uint_format_object_backend, components, bit_count);
    _vglyph_rgba_uint_format_ctor(format);

    return format;
}

vglyph_object_t*
vglyph_rgba_uint_format_to_object(vglyph_rgba_uint_format_t* format)
{
    assert(format);
    return &format->base.object;
}

vglyph_format_t*
vglyph_rgba_uint_format_to_format(vglyph_rgba_uint_format_t* format)
{
    assert(format);
    return &format->base;
}
