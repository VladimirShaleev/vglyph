/* vglyph - library for visualize glyphs
 *
 * File: vglyph-glyph.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-glyph.h"
#include "vglyph-figure.h"
#include "vglyph-type.h"

static void
_vglyph_glyph_init(vglyph_glyph_t* glyph,
                   const vglyph_object_backend_t* object_backend,
                   vglyph_figure_t* figure)
{
    _vglyph_object_init(&glyph->object, object_backend);

    glyph->figure               = _vglyph_figure_reference(figure);
    glyph->horizontal_bearing_x = 0.0f;
    glyph->horizontal_bearing_y = 0.0f;
    glyph->horizontal_advance   = 0.0f;
    glyph->vertical_bearing_x   = 0.0f;
    glyph->vertical_bearing_y   = 0.0f;
    glyph->vertical_advance     = 0.0f;
}

static void
_vglyph_glyph_ctor(vglyph_glyph_t* glyph)
{
    if (!_vglyph_figure_is_valid(glyph->figure))
    {
        _vglyph_glyph_set_state(glyph, _vglyph_figure_get_state(glyph->figure));
        return;
    }
}

static void
_vglyph_glyph_dtor(vglyph_glyph_t* glyph)
{
}

static vglyph_bool_t
_vglyph_glyph_is_cast(vglyph_type_t* type)
{
    return vglyph_get_glyph_type() == type;
}

static void
_vglyph_glyph_destroy_callback(vglyph_object_t* object)
{
    vglyph_glyph_t* glyph = (vglyph_glyph_t*)object;
    _vglyph_glyph_dtor(glyph);

    free(glyph);
}

static const vglyph_object_backend_t vglyph_glyph_object_backend = {
    vglyph_get_glyph_type,
    _vglyph_glyph_is_cast,
    _vglyph_glyph_destroy_callback
};

vglyph_type_t*
vglyph_get_glyph_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_glyph_is_cast);
    return &type;
}

vglyph_glyph_t*
vglyph_object_to_glyph(vglyph_object_t* object)
{
    assert(object);
    return (vglyph_glyph_t*)_vglyph_object_to_type(object, vglyph_get_glyph_type());
}

vglyph_object_t*
vglyph_glyph_to_object(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return &glyph->object;
}

vglyph_glyph_t*
vglyph_glyph_create(vglyph_figure_t* figure)
{
    vglyph_glyph_t* glyph = (vglyph_glyph_t*)malloc(sizeof(vglyph_glyph_t));

    if (!glyph)
        return (vglyph_glyph_t*)_vglyph_object_out_of_memory();

    _vglyph_glyph_init(glyph, &vglyph_glyph_object_backend, figure);
    _vglyph_glyph_ctor(glyph);

    return glyph;
}

vglyph_figure_t*
vglyph_glyph_get_figure(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return _vglyph_figure_reference(glyph->figure);
}

vglyph_float32_t
vglyph_glyph_get_width(vglyph_glyph_t* glyph)
{
    assert(glyph);

    vglyph_rectangle_t bound;
    _vglyph_figure_get_bound(glyph->figure, &bound);

    return bound.right - bound.left;
}

vglyph_float32_t
vglyph_glyph_get_height(vglyph_glyph_t* glyph)
{
    assert(glyph);

    vglyph_rectangle_t bound;
    _vglyph_figure_get_bound(glyph->figure, &bound);

    return bound.bottom - bound.top;
}

vglyph_float32_t
vglyph_glyph_get_horizontal_bearing_x(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return glyph->horizontal_bearing_x;
}

void
vglyph_glyph_set_horizontal_bearing_x(vglyph_glyph_t* glyph,
                                      vglyph_float32_t bearing_x)
{
    assert(glyph);
    glyph->horizontal_bearing_x = bearing_x;
}

vglyph_float32_t
vglyph_glyph_get_horizontal_bearing_y(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return glyph->horizontal_bearing_y;
}

void
vglyph_glyph_set_horizontal_bearing_y(vglyph_glyph_t* glyph,
                                      vglyph_float32_t bearing_y)
{
    assert(glyph);
    glyph->horizontal_bearing_y = bearing_y;
}

vglyph_float32_t
vglyph_glyph_get_horizontal_advance(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return glyph->horizontal_advance;
}

void
vglyph_glyph_set_horizontal_advance(vglyph_glyph_t* glyph,
                                    vglyph_float32_t advance)
{
    assert(glyph);
    glyph->horizontal_advance = advance;
}

vglyph_float32_t
vglyph_glyph_get_vertical_bearing_x(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return glyph->vertical_bearing_x;
}

void
vglyph_glyph_set_vertical_bearing_x(vglyph_glyph_t* glyph,
                                    vglyph_float32_t bearing_x)
{
    assert(glyph);
    glyph->vertical_bearing_x = bearing_x;
}

vglyph_float32_t
vglyph_glyph_get_vertical_bearing_y(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return glyph->vertical_bearing_y;
}

void
vglyph_glyph_set_vertical_bearing_y(vglyph_glyph_t* glyph,
                                    vglyph_float32_t bearing_y)
{
    assert(glyph);
    glyph->vertical_bearing_y = bearing_y;
}

vglyph_float32_t
vglyph_glyph_get_vertical_advance(vglyph_glyph_t* glyph)
{
    assert(glyph);
    return glyph->vertical_advance;
}

void
vglyph_glyph_set_vertical_advance(vglyph_glyph_t* glyph,
                                  vglyph_float32_t advance)
{
    assert(glyph);
    glyph->vertical_advance = advance;
}
