/* vglyph - library for visualize glyphs
 *
 * File: vglyph-segment.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-segment.h"

vglyph_segment_t*
vglyph_segment_reference(vglyph_segment_t* segment)
{
    assert(segment);
    return (vglyph_segment_t*)_vglyph_object_reference(&segment->object);
}

void
vglyph_segment_destroy(vglyph_segment_t* segment)
{
    assert(segment);
    _vglyph_object_destroy(&segment->object);
}

int
vglyph_segment_get_reference_count(vglyph_segment_t* segment)
{
    assert(segment);
    return _vglyph_object_get_reference_count(&segment->object);
}

vglyph_state_t
vglyph_segment_get_state(vglyph_segment_t* segment)
{
    assert(segment);
    return _vglyph_object_get_state(&segment->object);
}

vglyph_object_t*
vglyph_segment_segment_to_object(vglyph_segment_t* segment)
{
    assert(segment);
    return _vglyph_object_reference(&segment->object);
}

vglyph_segment_t*
vglyph_segment_object_to_segment(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_segment_t*)vglyph_object_to_type(object, VGLYPH_TYPE_SEGMENT);
}

vglyph_segment_type_t
vglyph_segment_get_type(vglyph_segment_t* segment)
{
    assert(segment);

    if (_vglyph_segment_is_valid(segment))
        return segment->type;

    return VGLYPH_SEGMENT_UNKNOWN;
}
