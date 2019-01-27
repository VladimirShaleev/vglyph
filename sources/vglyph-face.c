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

    face->charmap = NULL;
}

static void
_vglyph_face_ctor(vglyph_face_t* face)
{
    face->charmap = _vglyph_vector_create(sizeof(vglyph_charmap_t) * 8);

    if (!_vglyph_vector_is_valid(face->charmap))
    {
        _vglyph_face_set_state(face, _vglyph_vector_get_state(face->charmap));
        return;
    }
}

static void
_vglyph_face_dtor(vglyph_face_t* face)
{
    vglyph_vector_t* charmap = face->charmap;

    if (_vglyph_vector_is_valid(charmap))
    {
        vglyph_uint_t count = _vglyph_vector_size_in_bytes(charmap);
        vglyph_charmap_t* current;

        for (vglyph_uint_t offset = 0; offset < count; offset += sizeof(vglyph_charmap_t))
        {
            current = (vglyph_charmap_t*)_vglyph_vector_at(charmap, offset);
            _vglyph_glyph_destroy(current->glyph);
        }
    }
    
    _vglyph_vector_destroy(face->charmap);
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
    assert(face);

    if (_vglyph_face_is_valid(face))
    {
        vglyph_glyph_t* glyph = _vglyph_face_find_glyph(face, char_code, NULL);

        if (glyph)
            return _vglyph_glyph_reference(glyph);
    }

    return NULL;
}

void
vglyph_face_add_glyph(vglyph_face_t* face,
                      vglyph_glyph_t* glyph,
                      vglyph_uint32_t char_code)
{
    assert(face);
    assert(glyph);

    if (_vglyph_face_is_valid(face))
    {
        vglyph_vector_t*  charmap = face->charmap;
        vglyph_charmap_t* current;

        vglyph_uint_t count = _vglyph_vector_size_in_bytes(charmap);
        vglyph_uint_t find_offset;

        for (find_offset = 0; find_offset < count; find_offset += sizeof(vglyph_charmap_t))
        {
            current = (vglyph_charmap_t*)_vglyph_vector_at(charmap, find_offset);

            if (char_code < current->char_code)
                break;
        }

        vglyph_charmap_t new_charmap;
        new_charmap.glyph     = _vglyph_glyph_reference(glyph);
        new_charmap.char_code = char_code;

        vglyph_state_t state = _vglyph_vector_insert(charmap,
                                                     (vglyph_uint8_t*)&new_charmap,
                                                     sizeof(vglyph_charmap_t),
                                                     find_offset);

        if (state != VGLYPH_STATE_SUCCESS)
        {
            _vglyph_face_set_state(face, state);
            _vglyph_object_set_state_not_fatal(&face->object);
        }
    }
}

vglyph_bool_t
vglyph_face_remove_glyph(vglyph_face_t* face,
                         vglyph_uint32_t char_code)
{
    assert(face);

    if (_vglyph_face_is_valid(face))
    {
        vglyph_uint_t offset;
        vglyph_glyph_t* glyph = _vglyph_face_find_glyph(face, char_code, &offset);

        if (glyph)
        {
            _vglyph_vector_remove(face->charmap, sizeof(vglyph_charmap_t), offset);
            _vglyph_glyph_destroy(glyph);

            return TRUE;
        }
    }

    return FALSE;
}
