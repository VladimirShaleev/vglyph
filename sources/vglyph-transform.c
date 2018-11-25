/* vglyph - library for visualize glyphs
 *
 * File: vglyph-transform.c
 * Copyright (C) 2018 Shaleev Vladimir
 */

#include "vglyph-transform.h"
#include "vglyph-type.h"

static void
_vglyph_transform_init(vglyph_transform_t* transform,
                       const vglyph_object_backend_t* object_backend)
{
    _vglyph_object_init(&transform->object, object_backend);
}

static void
_vglyph_transform_ctor(vglyph_transform_t* transform, 
                       const vglyph_matrix_t* matrix)
{
    if (matrix)
        transform->matrix = *matrix;
    else
        _vglyph_matrix_identity(&transform->matrix);
}

static void
_vglyph_transform_dtor(vglyph_transform_t* transform)
{
}

static vglyph_bool_t
_vglyph_transform_is_cast(vglyph_type_t* type)
{
    return vglyph_get_transform_type() == type;
}

static void
_vglyph_transform_destroy_callback(vglyph_object_t* object)
{
    vglyph_transform_t* transform = (vglyph_transform_t*)object;
    _vglyph_transform_dtor(transform);

    free(transform);
}

static const vglyph_object_backend_t vglyph_transform_object_backend = {
    vglyph_get_transform_type,
    _vglyph_transform_is_cast,
    _vglyph_transform_destroy_callback
};

static vglyph_transform_t*
_vglyph_transform_create(const vglyph_matrix_t* matrix)
{
    vglyph_transform_t* transform = (vglyph_transform_t*)malloc(sizeof(vglyph_transform_t));

    if (!transform)
        return (vglyph_transform_t*)_vglyph_object_out_of_memory();

    _vglyph_transform_init(transform, &vglyph_transform_object_backend);
    _vglyph_transform_ctor(transform, matrix);

    return transform;
}

vglyph_type_t*
vglyph_get_transform_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_transform_is_cast);
    return &type;
}

vglyph_transform_t*
vglyph_object_to_transform(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_transform_t*)_vglyph_object_to_type(object, vglyph_get_transform_type());
}

vglyph_object_t*
vglyph_transform_to_object(vglyph_transform_t* transform)
{
    assert(transform);
    return &transform->object;
}

vglyph_transform_t*
vglyph_transform_create()
{
    return _vglyph_transform_create(NULL);
}

vglyph_transform_t*
vglyph_transform_create_copy(vglyph_transform_t* transform)
{
    assert(transform);
    return _vglyph_transform_create(&transform->matrix);
}

//void
//vglyph_glyph_set_advance(vglyph_glyph_t* glyph,
//                         vglyph_float32_t advance)
//{
//    assert(glyph);
//    glyph->advance = advance;
//}
