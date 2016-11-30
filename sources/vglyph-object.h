/* vglyph - library for visualize glyphs
 *
 * File: vglyph-object.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_OBJECT_H
#define VGLYPH_OBJECT_H

#include "vglyph-api.h"
#include "vglyph-types.h"

#define VGLYPH_REFERENCE_COUNT_INVALID (-1)

typedef void 
(*vglyph_object_destroy_func_t)(void* object);

typedef struct
{
    int ref_count;
    vglyph_state_t state;
    vglyph_object_destroy_func_t destroy_func;
} vglyph_object_t;

vglyph_object_t*
_vglyph_object_out_of_memory();

static inline void
_vglyph_object_init(vglyph_object_t* object,
                    vglyph_object_destroy_func_t destroy_func)
{
    assert(object);
    assert(destroy_func);

    object->ref_count    = 1;
    object->state        = VGLYPH_STATE_SUCCESS;
    object->destroy_func = destroy_func;
}

static inline vglyph_object_t*
_vglyph_object_reference(vglyph_object_t* object)
{
    assert(object);

    if (object->ref_count != VGLYPH_REFERENCE_COUNT_INVALID)
        ++object->ref_count;

    return object;
}

static inline void
_vglyph_object_destroy(vglyph_object_t* object)
{
    assert(object);

    if (object->ref_count != VGLYPH_REFERENCE_COUNT_INVALID)
    {
        if (--object->ref_count == 0)
            object->destroy_func(object);
    }
}

static inline int
_vglyph_object_get_reference_count(vglyph_object_t* object)
{
    assert(object);
    return object->ref_count;
}

static inline vglyph_state_t
_vglyph_object_get_state(vglyph_object_t* object)
{
    assert(object);
    return object->state;
}

static inline void
_vglyph_object_set_state(vglyph_object_t* object,
                        vglyph_state_t state)
{
    assert(object);
    object->state = state;
}

static inline vglyph_bool_t
_vglyph_object_is_valid(vglyph_object_t* object)
{
    assert(object);
    return object->state == VGLYPH_STATE_SUCCESS;
}

#endif
