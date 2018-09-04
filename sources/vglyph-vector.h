/* vglyph - library for visualize glyphs
 *
 * File: vglyph-vector.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_VECTOR_H
#define VGLYPH_VECTOR_H

#include "vglyph-object.h"

extern const vglyph_object_backend_t _vglyph_vector_object_backend;

typedef struct _vglyph_vector
{
    vglyph_object_t object;
    vglyph_uint8_t* data;
    vglyph_uint_t   reserved_bytes;
    vglyph_uint_t   count_bytes;
    vglyph_uint_t   max_bytes;
} vglyph_vector_t;

vglyph_type_t*
_vglyph_vector_get_type(void);

static inline vglyph_vector_t*
_vglyph_object_to_vector(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_vector_t*)_vglyph_object_to_type(object, _vglyph_vector_get_type());
}

static inline void
_vglyph_vector_set_state(vglyph_vector_t* vector,
                         vglyph_state_t state)
{
    assert(vector);
    _vglyph_object_set_state(&vector->object, state);
}

static inline vglyph_bool_t
_vglyph_vector_is_valid(vglyph_vector_t* vector)
{
    assert(vector);
    return _vglyph_object_is_valid(&vector->object);
}

static inline void
_vglyph_vector_init(vglyph_vector_t* vector,
                    const vglyph_object_backend_t* object_backend)
{
    _vglyph_object_init(&vector->object, object_backend);

    vector->data           = NULL;
    vector->reserved_bytes = 0;
    vector->count_bytes    = 0;
    vector->max_bytes      = 0;
}

static inline void
_vglyph_vector_ctor(vglyph_vector_t* vector,
                    vglyph_uint_t reserved_bytes)
{
    vector->reserved_bytes = reserved_bytes;
    vector->max_bytes      = reserved_bytes;

    vector->data = (vglyph_uint8_t*)malloc(vector->max_bytes);

    if (!vector->data)
    {
        _vglyph_vector_set_state(vector, VGLYPH_STATE_OUT_OF_MEMORY);
        return;
    }
}

static inline void
_vglyph_vector_dtor(vglyph_vector_t* vector)
{
    free(vector->data);
    vector->data = NULL;
}

static inline vglyph_vector_t*
_vglyph_vector_create(vglyph_uint_t reserved_bytes)
{
    vglyph_vector_t* vector = (vglyph_vector_t*)malloc(sizeof(vglyph_vector_t));

    if (!vector)
        return (vglyph_vector_t*)_vglyph_object_out_of_memory();

    _vglyph_vector_init(vector, &_vglyph_vector_object_backend);
    _vglyph_vector_ctor(vector, reserved_bytes);

    return vector;
}

static inline vglyph_vector_t*
_vglyph_vector_reference(vglyph_vector_t* vector)
{
    assert(vector);
    return (vglyph_vector_t*)_vglyph_object_reference(&vector->object);
}

static inline void
_vglyph_vector_destroy(vglyph_vector_t* vector)
{
    assert(vector);
    _vglyph_object_destroy(&vector->object);
}

static inline int
_vglyph_vector_get_reference_count(vglyph_vector_t* vector)
{
    assert(vector);
    return _vglyph_object_get_reference_count(&vector->object);
}

static inline vglyph_state_t
_vglyph_vector_get_state(vglyph_vector_t* vector)
{
    assert(vector);
    return _vglyph_object_get_state(&vector->object);
}

static inline vglyph_object_t*
_vglyph_vector_to_object(vglyph_vector_t* vector)
{
    assert(vector);
    return &vector->object;
}

static inline vglyph_uint_t
_vglyph_vector_push(vglyph_vector_t* vector,
                    vglyph_uint_t bytes)
{
    assert(vector);
    assert(_vglyph_vector_is_valid(vector));

    vglyph_uint_t offset = vector->count_bytes;
    vector->count_bytes += bytes;

    if (vector->count_bytes > vector->max_bytes)
    {
        vector->max_bytes += vector->reserved_bytes;
        vector->data = (vglyph_uint8_t*)realloc(vector->data, vector->max_bytes);

        if (!vector->data)
        {
            _vglyph_vector_set_state(vector, VGLYPH_STATE_OUT_OF_MEMORY);
            return 0;
        }
    }

    return offset;
}

static inline vglyph_state_t
_vglyph_vector_add(vglyph_vector_t* vector, 
                   const vglyph_uint8_t* data,
                   vglyph_uint_t bytes)
{
    assert(vector);
    assert(data);
    assert(_vglyph_vector_is_valid(vector));

    vglyph_uint_t offset = _vglyph_vector_push(vector, bytes);
    vglyph_state_t state = _vglyph_vector_get_state(vector);

    if (state == VGLYPH_STATE_SUCCESS)
        memcpy(vector->data + offset, data, (size_t)bytes);

    return state;
}

static inline vglyph_uint_t
_vglyph_vector_insert(vglyph_vector_t* vector,
                      const vglyph_uint8_t* data,
                      vglyph_uint_t bytes,
                      vglyph_uint_t offset)
{
    assert(vector);
    assert(data);
    assert(_vglyph_vector_is_valid(vector));

    if (offset >= vector->count_bytes)
    {
        const vglyph_uint_t add_bytes = offset + bytes - vector->count_bytes;
        _vglyph_vector_push(vector, add_bytes);
    }
    else
    {
        const size_t shift_bytes = (size_t)(vector->count_bytes - offset);
        _vglyph_vector_push(vector, bytes);

        if (_vglyph_vector_is_valid(vector))
            memmove(vector->data + offset + bytes, vector->data + offset, shift_bytes);
    }

    vglyph_state_t state = _vglyph_vector_get_state(vector);

    if (state == VGLYPH_STATE_SUCCESS)
        memcpy(vector->data + offset, data, (size_t)bytes);

    return state;
}

static inline void*
_vglyph_vector_at(vglyph_vector_t* vector, 
                  vglyph_uint_t offset)
{
    assert(vector);
    assert(_vglyph_vector_is_valid(vector));
    assert(offset < vector->count_bytes);

    return vector->data + offset;
}

static inline void
_vglyph_vector_clear(vglyph_vector_t* vector)
{
    assert(vector);
    assert(_vglyph_vector_is_valid(vector));

    free(vector->data);

    vector->data = NULL;
    vector->count_bytes = 0; 
    
    _vglyph_vector_ctor(vector, vector->reserved_bytes);
}

static inline vglyph_uint_t
_vglyph_vector_size_in_bytes(vglyph_vector_t* vector)
{
    assert(vector);
    assert(_vglyph_vector_is_valid(vector));

    return vector->count_bytes;
}

#endif
