﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-data-surface.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_DATA_SURFACE_H
#define VGLYPH_DATA_SURFACE_H

#include "vglyph-surface.h"
#include "vglyph-vector.h"
#include "vglyph-matrix.h"

extern const vglyph_surface_backend_t vglyph_data_surface_backend;

typedef struct _vglyph_data_surface
{
    vglyph_surface_t base;
    vglyph_uint8_t*  data;
    vglyph_uint8_t*  data_back;
    vglyph_uint_t    shift_mulitsampling;
} vglyph_data_surface_t;

void
_vglyph_data_surface_init(vglyph_data_surface_t* surface,
                          const vglyph_object_backend_t* object_backend,
                          const vglyph_surface_backend_t* surface_backend,
                          vglyph_format_t* format,
                          vglyph_render_t* render,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height,
                          vglyph_uint32_t pitch,
                          vglyph_uint8_t* data);

void
_vglyph_data_surface_ctor(vglyph_data_surface_t* surface);

void
_vglyph_data_surface_dtor(vglyph_data_surface_t* surface);

vglyph_bool_t
_vglyph_data_surface_is_cast(vglyph_type_t* type);

vglyph_type_t*
_vglyph_data_surface_get_type(void);

void 
_vglyph_data_surface_update_multisampling(vglyph_surface_t* surface);

vglyph_uint8_t*
_vglyph_data_surface_lock(vglyph_surface_t* surface,
                          vglyph_uint32_t x,
                          vglyph_uint32_t y,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height);

void
_vglyph_data_surface_unlock(vglyph_surface_t* surface);

void
_vglyph_data_surface_fill(vglyph_surface_t* surface,
                          vglyph_uint32_t x,
                          vglyph_uint32_t y,
                          vglyph_uint32_t width,
                          vglyph_uint32_t height,
                          const vglyph_color_t* color);

void
_vglyph_data_surface_get_pixel(vglyph_surface_t* surface,
                               vglyph_sint32_t x,
                               vglyph_sint32_t y,
                               vglyph_color_t* color);

void
_vglyph_data_surface_set_pixel(vglyph_surface_t* surface,
                               vglyph_sint32_t x,
                               vglyph_sint32_t y,
                               const vglyph_color_t* color);

vglyph_uint_t
_vglyph_data_surface_get_dpi(vglyph_surface_t* surface);

vglyph_bool_t
_vglyph_data_surface_draw_glyph(vglyph_surface_t* surface,
                                vglyph_glyph_t* glyph,
                                vglyph_float32_t pt,
                                const vglyph_color_t* color,
                                const vglyph_point_t* position,
                                const vglyph_point_t* origin,
                                const vglyph_point_t* scale,
                                vglyph_float32_t angle,
                                vglyph_bool_t vertical_layout,
                                vglyph_point_t* next_position);

vglyph_bool_t
_vglyph_data_surface_draw_glyph_viewport(vglyph_surface_t* surface,
                                         vglyph_glyph_t* glyph,
                                         const vglyph_color_t* color,
                                         const vglyph_point_t* position,
                                         const vglyph_point_t* viewport,
                                         const vglyph_point_t* origin,
                                         vglyph_float32_t angle,
                                         vglyph_bool_t fit_to_viewport);

vglyph_bool_t
_vglyph_data_surface_draw_glyph_transform(vglyph_surface_t* surface,
                                          vglyph_glyph_t* glyph,
                                          const vglyph_color_t* color,
                                          const vglyph_transform_t* transform);

vglyph_uint32_t
_vglyph_data_surface_get_pitch(vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_alignment_t row_alignment);

vglyph_render_t*
_vglyph_data_surface_create_render(vglyph_format_t* format);

static inline void
_vglyph_data_surface_set_state(vglyph_data_surface_t* surface,
                               vglyph_state_t state)
{
    assert(surface);
    _vglyph_surface_set_state(&surface->base, state);
}

static inline vglyph_bool_t
_vglyph_data_surface_is_valid(vglyph_data_surface_t* surface)
{
    assert(surface);
    return _vglyph_surface_is_valid(&surface->base);
}

static inline vglyph_float32_t
_vglyph_data_surface_pt_to_px(vglyph_data_surface_t* surface,
                              vglyph_float32_t pt)
{
    assert(surface);
    return pt * surface->base.backend->get_dpi(&surface->base) / 72.0f;
}

static inline vglyph_state_t
_vglyph_data_surface_add_point(vglyph_vector_t* points, 
                               const vglyph_matrix_t* matrix,
                               const vglyph_point_t* point)
{
    assert(points);
    assert(point);

    vglyph_point_t transform_point;
    _vglyph_matrix_transform_point(&transform_point, matrix, point);

    return _vglyph_vector_add(points, (const vglyph_uint8_t*)&transform_point, sizeof(vglyph_point_t));
}

#endif
