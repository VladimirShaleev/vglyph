/* vglyph - library for visualize glyphs
 *
 * File: vglyph-face.c
 * Copyright (C) 2019 Shaleev Vladimir
 */

#include "vglyph-face.h"
#include "vglyph-type.h"

static void
_vglyph_face_init(vglyph_face_t* face,
                  const vglyph_object_backend_t* object_backend)
{
    _vglyph_object_init(&face->object, object_backend);
}

static void
_vglyph_face_ctor(vglyph_face_t* face)
{
}

static void
_vglyph_face_dtor(vglyph_face_t* face)
{
}

static vglyph_bool_t
_vglyph_face_is_cast(vglyph_type_t* type)
{
    return vglyph_get_face_type() == type;
}

static void
_vglyph_face_destroy_callback(vglyph_object_t* object)
{
    vglyph_face_t* face = (vglyph_face_t*)object;
    _vglyph_face_dtor(face);

    free(face);
}

static const vglyph_object_backend_t vglyph_face_object_backend = {
    vglyph_get_face_type,
    _vglyph_face_is_cast,
    _vglyph_face_destroy_callback
};

vglyph_type_t*
vglyph_get_face_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_face_is_cast);
    return &type;
}

vglyph_face_t*
vglyph_object_to_face(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_face_t*)_vglyph_object_to_type(object, vglyph_get_face_type());
}

vglyph_object_t*
vglyph_face_to_object(vglyph_face_t* face)
{
    assert(face);
    return &face->object;
}

vglyph_face_t*
vglyph_face_create(void)
{
    vglyph_face_t* face = (vglyph_face_t*)malloc(sizeof(vglyph_face_t));

    if (!face)
        return (vglyph_face_t*)_vglyph_object_out_of_memory();

    _vglyph_face_init(face, &vglyph_face_object_backend);
    _vglyph_face_ctor(face);

    return face;
}

vglyph_glyph_t*
vglyph_face_get_glyph(vglyph_face_t* face,
                      vglyph_uint32_t char_code)
{
}

void
vglyph_face_add_glyph(vglyph_face_t* face,
                      vglyph_glyph_t* glyph,
                      vglyph_uint32_t char_code)
{
}

vglyph_bool_t
vglyph_face_remove_glyph(vglyph_face_t* face,
                         vglyph_uint32_t char_code)
{
}
