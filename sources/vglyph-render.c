/* vglyph - library for visualize glyphs
 *
 * File: vglyph-render.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include "vglyph-render.h"
#include "vglyph-type.h"

void
_vglyph_render_init(vglyph_render_t* render,
                    const vglyph_object_backend_t* object_backend,
                    const vglyph_render_backend_t* render_backend)
{
    assert(render);
    assert(object_backend);
    assert(render_backend);

    _vglyph_object_init(&render->object, object_backend);

    render->backend = render_backend;
}

void
_vglyph_render_ctor(vglyph_render_t* render)
{
}

void
_vglyph_render_dtor(vglyph_render_t* render)
{
}

vglyph_bool_t
_vglyph_render_is_cast(vglyph_type_t* type)
{
    return _vglyph_render_get_type() == type;
}

vglyph_type_t*
_vglyph_render_get_type(void)
{
    static vglyph_type_t type = _vglyph_type_create(_vglyph_render_is_cast);
    return &type;
}
