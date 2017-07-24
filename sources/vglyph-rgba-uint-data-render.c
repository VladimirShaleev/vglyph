/* vglyph - library for visualize glyphs
 *
 * File: vglyph-rgba-uint-data-render.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-rgba-uint-data-render.h"
#include "vglyph-type.h"

void
_vglyph_rgba_uint_data_render_init(vglyph_rgba_uint_data_render_t* render,
                                   const vglyph_object_backend_t* object_backend,
                                   const vglyph_render_backend_t* render_backend)
{
    assert(render);
    assert(object_backend);
    assert(render_backend);

    _vglyph_render_init(&render->base, object_backend, render_backend);
}

void
_vglyph_rgba_uint_data_render_ctor(vglyph_rgba_uint_data_render_t* render)
{
    _vglyph_render_ctor(&render->base);

    if (_vglyph_rgba_uint_data_render_is_valid(render))
    {
    }
}

void
_vglyph_rgba_uint_data_render_dtor(vglyph_rgba_uint_data_render_t* render)
{
    _vglyph_render_dtor(&render->base);
}

vglyph_bool_t
_vglyph_rgba_uint_data_render_is_cast(vglyph_type_t* type)
{
    return _vglyph_rgba_uint_data_render_get_type() == type
        || _vglyph_render_is_cast(type);
}

vglyph_type_t*
_vglyph_rgba_uint_data_render_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_rgba_uint_data_render_is_cast);
    return &type;
}

static void
_vglyph_rgba_uint_data_render_destroy(vglyph_object_t* object)
{
    vglyph_rgba_uint_data_render_t* render = (vglyph_rgba_uint_data_render_t*)object;
    _vglyph_rgba_uint_data_render_dtor(render);

    free(render);
}

static void _vglyph_rgba_uint_data_render_set_pixel(vglyph_render_t* render,
                                                    vglyph_surface_t* surface,
                                                    vglyph_float32_t x,
                                                    vglyph_float32_t y,
                                                    const vglyph_color_t* color)
{

}

static const vglyph_object_backend_t vglyph_rgba_uint_data_render_object_backend = {
    _vglyph_rgba_uint_data_render_get_type,
    _vglyph_rgba_uint_data_render_is_cast,
    _vglyph_rgba_uint_data_render_destroy
};

static const vglyph_render_backend_t vglyph_rgba_uint_data_render_backend = {
    _vglyph_rgba_uint_data_render_set_pixel
};

vglyph_render_t*
_vglyph_rgba_uint_data_render_create()
{
    vglyph_rgba_uint_data_render_t* render = 
        (vglyph_rgba_uint_data_render_t*)malloc(sizeof(vglyph_rgba_uint_data_render_t));

    if (!render)
        return (vglyph_render_t*)_vglyph_object_out_of_memory();

    _vglyph_rgba_uint_data_render_init(render, 
                                       &vglyph_rgba_uint_data_render_object_backend,
                                       &vglyph_rgba_uint_data_render_backend);

    _vglyph_rgba_uint_data_render_ctor(render);

    return &render->base;
}
