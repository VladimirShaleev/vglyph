/* vglyph - library for visualize glyphs
 *
 * File: vglyph-vector.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_VECTOR_H
#define VGLYPH_VECTOR_H

#include "vglyph-object.h"

typedef struct _vglyph_vector
{
    vglyph_object_t object;
    vglyph_uint8_t* data;
    vglyph_uint_t   reserved_bytes;
    vglyph_uint_t   count_bytes;
    vglyph_uint_t   max_bytes;
} vglyph_vector_t;

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
                    vglyph_object_is_cast_func_t is_cast_func,
                    vglyph_object_destroy_func_t destroy_func)
{
    _vglyph_object_init(&vector->object, is_cast_func, destroy_func);

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

    vector->data = malloc(vector->max_bytes);

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

static inline vglyph_bool_t
_vglyph_vector_is_cast_callback(vglyph_object_t* object,
                                vglyph_type_t type)
{
    return type == VGLYPH_TYPE_VECTOR ? TRUE : FALSE;
}

static inline void
_vglyph_vector_destroy_callback(void* object)
{
    vglyph_vector_t* vector = (vglyph_vector_t*)object;
    _vglyph_vector_dtor(vector);

    free(vector);
}

static inline vglyph_vector_t*
_vglyph_vector_create(vglyph_uint_t reserved_bytes)
{
    vglyph_vector_t* vector = (vglyph_vector_t*)malloc(sizeof(vglyph_vector_t));

    if (!vector)
        return (vglyph_vector_t*)_vglyph_object_out_of_memory();

    _vglyph_vector_init(vector,
                        NULL,
                        _vglyph_vector_destroy_callback);

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
        vector->data = realloc(vector->data, vector->max_bytes);

        if (!vector->data)
        {
            _vglyph_vector_set_state(vector, VGLYPH_STATE_OUT_OF_MEMORY);
            return 0;
        }
    }

    return offset;
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

#endif
