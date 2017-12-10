/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint-format.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-rgba-uint-format.h"
#include "vglyph-type.h"

void
_vglyph_rgba_uint_format_init(vglyph_rgba_uint_format_t* format,
                              const vglyph_object_backend_t* object_backend,
                              const vglyph_format_backend_t* format_backend,
                              const vglyph_packaging_bytes_t* packaging_bytes,
                              const vglyph_rgba_components_t* components,
                              const vglyph_rgba_uint_bit_count_t* bit_count)
{
    _vglyph_format_init(&format->base, object_backend, format_backend, packaging_bytes);

    format->components      = *components;
    format->bit_count       = *bit_count;
}

void
_vglyph_rgba_uint_format_ctor(vglyph_rgba_uint_format_t* format)
{
    _vglyph_format_ctor(&format->base);

    if (_vglyph_rgba_uint_format_is_valid(format))
    {
        if (format->bit_count.r > (sizeof(format->capacity.r) << 3) ||
            format->bit_count.g > (sizeof(format->capacity.g) << 3) ||
            format->bit_count.b > (sizeof(format->capacity.b) << 3) ||
            format->bit_count.a > (sizeof(format->capacity.a) << 3))
        {
            _vglyph_rgba_uint_format_set_state(format, VGLYPH_STATE_INVALID_FORMAT);
            return;
        }

        format->capacity.r = _vglyph_rgba_uint_format_get_capacity(format->bit_count.r);
        format->capacity.g = _vglyph_rgba_uint_format_get_capacity(format->bit_count.g);
        format->capacity.b = _vglyph_rgba_uint_format_get_capacity(format->bit_count.b);
        format->capacity.a = _vglyph_rgba_uint_format_get_capacity(format->bit_count.a);

        format->inv_capacity.r = _vglyph_rgba_uint_format_get_inv_capacity(format->capacity.r);
        format->inv_capacity.g = _vglyph_rgba_uint_format_get_inv_capacity(format->capacity.g);
        format->inv_capacity.b = _vglyph_rgba_uint_format_get_inv_capacity(format->capacity.b);
        format->inv_capacity.a = _vglyph_rgba_uint_format_get_inv_capacity(format->capacity.a);
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

static vglyph_uint32_t
_vglyph_rgba_uint_format_get_bits_per_pixel(vglyph_format_t* format)
{
    vglyph_rgba_uint_format_t* rgba_uint_format = (vglyph_rgba_uint_format_t*)format;

    return (vglyph_uint32_t)
        rgba_uint_format->bit_count.r +
        rgba_uint_format->bit_count.g +
        rgba_uint_format->bit_count.b +
        rgba_uint_format->bit_count.a;
}

static const vglyph_object_backend_t vglyph_rgba_uint_format_object_backend = {
    vglyph_get_rgba_uint_format_type,
    _vglyph_rgba_uint_format_is_cast,
    _vglyph_rgba_uint_format_destroy
};

static const vglyph_format_backend_t vglyph_rgba_uint_format_backend = {
    _vglyph_rgba_uint_format_get_bits_per_pixel,
};

vglyph_type_t*
vglyph_get_rgba_uint_format_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_rgba_uint_format_is_cast);
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
vglyph_rgba_uint_format_create(const vglyph_packaging_bytes_t* packaging_bytes,
                               const vglyph_rgba_components_t* components,
                               const vglyph_rgba_uint_bit_count_t* bit_count)
{
    assert(packaging_bytes);
    assert(components);
    assert(bit_count);
    assert(packaging_bytes->byte_count >= 1);
    assert(packaging_bytes->endianness >= VGLYPH_ENDIANNESS_HOST && packaging_bytes->endianness <= VGLYPH_ENDIANNESS_LITTLE);
    assert(components->r >= VGLYPH_COMPONENT_ZERO && components->r <= VGLYPH_COMPONENT_ALPHA);
    assert(components->g >= VGLYPH_COMPONENT_ZERO && components->g <= VGLYPH_COMPONENT_ALPHA);
    assert(components->b >= VGLYPH_COMPONENT_ZERO && components->b <= VGLYPH_COMPONENT_ALPHA);
    assert(components->a >= VGLYPH_COMPONENT_ZERO && components->a <= VGLYPH_COMPONENT_ALPHA);

    vglyph_rgba_uint_format_t* format = (vglyph_rgba_uint_format_t*)malloc(sizeof(vglyph_rgba_uint_format_t));

    if (!format)
        return (vglyph_rgba_uint_format_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_uint_format_init(format, 
                                  &vglyph_rgba_uint_format_object_backend, 
                                  &vglyph_rgba_uint_format_backend, 
                                  packaging_bytes,
                                  components, 
                                  bit_count);

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

void
vglyph_rgba_uint_format_get_components(vglyph_rgba_uint_format_t* format,
                                       vglyph_rgba_components_t* components)
{
    assert(format);
    assert(components);

    if (_vglyph_rgba_uint_format_is_valid(format))
        *components = format->components;
}

void
vglyph_rgba_uint_format_get_bit_count(vglyph_rgba_uint_format_t* format,
                                      vglyph_rgba_uint_bit_count_t* bit_count)
{
    assert(format);
    assert(bit_count);

    if (_vglyph_rgba_uint_format_is_valid(format))
        *bit_count = format->bit_count;
}
