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
#define VGLYPH_STATE_NOT_FATAL         (((vglyph_state_t)-1) << ((sizeof(vglyph_state_t) << 3) - 1))

typedef struct _vglyph_object_backend
{
    vglyph_type_t* (*get_type)(void);
    vglyph_bool_t  (*is_cast)(vglyph_type_t* type);
    void           (*destroy)(vglyph_object_t* object);
} vglyph_object_backend_t;

struct _vglyph_object
{
    vglyph_sint32_t ref_count;
    vglyph_state_t state;
    const vglyph_object_backend_t* backend;
};

vglyph_object_t*
_vglyph_object_out_of_memory(void);

vglyph_object_t*
_vglyph_object_invalid_cast(void);

vglyph_object_t*
_vglyph_object_invalid_format(void);

vglyph_object_t*
_vglyph_object_to_type(vglyph_object_t* object,
                       vglyph_type_t* type);

static inline void
_vglyph_object_init(vglyph_object_t* object,
                    const vglyph_object_backend_t* backend)
{
    assert(object);
    assert(backend);

    object->ref_count = 1;
    object->state     = VGLYPH_STATE_SUCCESS;
    object->backend   = backend;
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
            object->backend->destroy(object);
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
    return object->state & ~VGLYPH_STATE_NOT_FATAL;
}

static inline void
_vglyph_object_set_state(vglyph_object_t* object,
                         vglyph_state_t state)
{
    assert(object);
    object->state = state & ~VGLYPH_STATE_NOT_FATAL;
}

static inline void
_vglyph_object_set_state_not_fatal(vglyph_object_t* object)
{
    assert(object);
    object->state |= VGLYPH_STATE_NOT_FATAL;
}

static inline vglyph_bool_t
_vglyph_object_is_valid(vglyph_object_t* object)
{
    assert(object);
    return object->state == VGLYPH_STATE_SUCCESS;
}

static inline vglyph_type_t*
_vglyph_object_get_type(vglyph_object_t* object)
{
    assert(object);
    return object->backend->get_type();
}

#endif
