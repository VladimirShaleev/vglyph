/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-format.h"
#include "vglyph-type.h"
#include "vglyph-format-parser.h"

void
_vglyph_format_init(vglyph_format_t* format,
                    const vglyph_object_backend_t* object_backend,
                    const vglyph_format_backend_t* format_backend,
                    const vglyph_packaging_bytes_t* packaging_bytes)
{
    assert(format_backend);
    assert(packaging_bytes);
    assert(packaging_bytes->byte_count >= 1);
    assert(packaging_bytes->endianness >= VGLYPH_ENDIANNESS_HOST && packaging_bytes->endianness <= VGLYPH_ENDIANNESS_LITTLE);

    _vglyph_object_init(&format->object, object_backend);

    format->backend = format_backend;
    format->packaging_bytes = *packaging_bytes;
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
_vglyph_format_destroy_callback(vglyph_object_t* object)
{
    vglyph_format_t* format = (vglyph_format_t*)object;
    _vglyph_format_dtor(format);

    free(format);
}

static const vglyph_object_backend_t vglyph_format_object_backend = {
    vglyph_get_format_type,
    _vglyph_format_is_cast,
    _vglyph_format_destroy_callback
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

vglyph_format_t*
vglyph_format_create(const char* format,
                     vglyph_endianness_t endianness)
{
    assert(format);

    vglyph_rgba_components_t components;
    vglyph_sint_t channels[4];
    vglyph_uint_t byte_count;

    vglyph_format_type_t type = _vglyph_format_parse(format, &components, channels, &byte_count);

    if (type != VGLYPH_FORMAT_TYPE_UNKNOWN)
    {
        vglyph_packaging_bytes_t packaging_bytes;
        packaging_bytes.byte_count = byte_count;
        packaging_bytes.endianness = endianness;
        
        if (type == VGLYPH_FORMAT_TYPE_UINT)
        {
            vglyph_rgba_uint_bit_count_t bit_count;
            bit_count.r = channels[0] < 0 ? 0 : channels[0];
            bit_count.g = channels[1] < 0 ? 0 : channels[1];
            bit_count.b = channels[2] < 0 ? 0 : channels[2];
            bit_count.a = channels[3] < 0 ? 0 : channels[3];

            return vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count);
        }
    }

    return (vglyph_format_t*)_vglyph_object_invalid_format();
}

vglyph_object_t*
vglyph_format_to_object(vglyph_format_t* format)
{
    assert(format);
    return &format->object;
}

vglyph_uint32_t
vglyph_format_get_bits_per_pixel(vglyph_format_t* format)
{
    assert(format);

    if (_vglyph_format_is_valid(format))
        return (vglyph_uint32_t)format->backend->get_bits_per_pixel(format);

    return 0;
}

void
vglyph_format_get_packaging_bytes(vglyph_format_t* format,
                                  vglyph_packaging_bytes_t* packaging_bytes)
{
    assert(format);
    assert(packaging_bytes);

    if (_vglyph_format_is_valid(format))
        *packaging_bytes = format->packaging_bytes;
}
