/* vglyph - library for visualize glyphs
 *
 * File: vglyph.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_H
#define VGLYPH_H

#include "vglyph-config.h"
#include "vglyph-platform.h"

#define VGLYPH_VERSION_MAJON 1
#define VGLYPH_VERSION_MINOR 0
#define VGLYPH_VERSION_MICRO 0

#define VGLYPH_VERSION_ENCODE(major, minor, micro)     ((major) << 16 | (minor) << 8 | (micro))
#define VGLYPH_VERSION_STRINGIZE_(major, minor, micro) #major "." #minor "." #micro
#define VGLYPH_VERSION_STRINGIZE(major, minor, micro)  VGLYPH_VERSION_STRINGIZE_(major, minor, micro)

#define VGLYPH_VERSION VGLYPH_VERSION_ENCODE( \
    VGLYPH_VERSION_MAJON, \
    VGLYPH_VERSION_MINOR, \
    VGLYPH_VERSION_MICRO)

#define VGLYPH_VERSION_STRING VGLYPH_VERSION_STRINGIZE( \
    VGLYPH_VERSION_MAJON, \
    VGLYPH_VERSION_MINOR, \
    VGLYPH_VERSION_MICRO)

VGLYPH_BEGIN

typedef struct _vglyph_object            vglyph_object_t;
typedef struct _vglyph_type              vglyph_type_t;
typedef struct _vglyph_figure            vglyph_figure_t;
typedef struct _vglyph_glyph             vglyph_glyph_t;
typedef struct _vglyph_format            vglyph_format_t;
typedef struct _vglyph_rgba_uint_format  vglyph_rgba_uint_format_t;
typedef struct _vglyph_rgba_float_format vglyph_rgba_float_format_t;
typedef struct _vglyph_transform         vglyph_transform_t;
typedef struct _vglyph_surface           vglyph_surface_t;

typedef _vglyph_bool    vglyph_bool_t;
typedef _vglyph_sint8   vglyph_sint8_t;
typedef _vglyph_uint8   vglyph_uint8_t;
typedef _vglyph_sint16  vglyph_sint16_t;
typedef _vglyph_uint16  vglyph_uint16_t;
typedef _vglyph_sint32  vglyph_sint32_t;
typedef _vglyph_uint32  vglyph_uint32_t;
typedef _vglyph_sint64  vglyph_sint64_t;
typedef _vglyph_uint64  vglyph_uint64_t;
typedef _vglyph_float32 vglyph_float32_t;
typedef _vglyph_float64 vglyph_float64_t;

#define VGLYPH_FORMAT_R4G4_UINT          "R4G4_UINT"
#define VGLYPH_FORMAT_R4G4B4A4_UINT      "R4G4B4A4_UINT"
#define VGLYPH_FORMAT_B4G4R4A4_UINT      "B4G4R4A4_UINT"
#define VGLYPH_FORMAT_A4R4G4B4_UINT      "A4R4G4B4_UINT"
#define VGLYPH_FORMAT_R5G6B5_UINT        "R5G6B5_UINT"
#define VGLYPH_FORMAT_B5G6R5_UINT        "B5G6R5_UINT"
#define VGLYPH_FORMAT_R5G5B5A1_UINT      "R5G5B5A1_UINT"
#define VGLYPH_FORMAT_B5G5R5A1_UINT      "B5G5R5A1_UINT"
#define VGLYPH_FORMAT_A1R5G5B5_UINT      "A1R5G5B5_UINT"
#define VGLYPH_FORMAT_R8_UINT            "R8_UINT"
#define VGLYPH_FORMAT_R8G8_UINT          "R8G8_UINT"
#define VGLYPH_FORMAT_R8G8B8_UINT        "R8G8B8_UINT"
#define VGLYPH_FORMAT_B8G8R8_UINT        "B8G8R8_UINT"
#define VGLYPH_FORMAT_R8G8B8A8_UINT      "R8G8B8A8_UINT"
#define VGLYPH_FORMAT_B8G8R8A8_UINT      "B8G8R8A8_UINT"
#define VGLYPH_FORMAT_A8R8G8B8_UINT      "A8R8G8B8_UINT"
#define VGLYPH_FORMAT_A8B8G8R8_UINT      "A8B8G8R8_UINT"
#define VGLYPH_FORMAT_A2R10G10B10_UINT   "A2R10G10B10_UINT"
#define VGLYPH_FORMAT_A2B10G10R10_UINT   "A2B10G10R10_UINT"
#define VGLYPH_FORMAT_R16_UINT           "R16_UINT"
#define VGLYPH_FORMAT_R16G16_UINT        "R16G16_UINT"
#define VGLYPH_FORMAT_R16G16B16_UINT     "R16G16B16_UINT"
#define VGLYPH_FORMAT_R16G16B16A16_UINT  "R16G16B16A16_UINT"
#define VGLYPH_FORMAT_R32_UINT           "R32_UINT"
#define VGLYPH_FORMAT_R32G32_UINT        "R32G32_UINT"
#define VGLYPH_FORMAT_R32G32B32_UINT     "R32G32B32_UINT"
#define VGLYPH_FORMAT_R32G32B32A32_UINT  "R32G32B32A32_UINT"
#define VGLYPH_FORMAT_R64_UINT           "R64_UINT"
#define VGLYPH_FORMAT_R64G64_UINT        "R64G64_UINT"
#define VGLYPH_FORMAT_R64G64B64_UINT     "R64G64B64_UINT"
#define VGLYPH_FORMAT_R64G64B64A64_UINT  "R64G64B64A64_UINT"
#define VGLYPH_FORMAT_R16_FLOAT          "R16_FLOAT"
#define VGLYPH_FORMAT_R16G16_FLOAT       "R16G16_FLOAT"
#define VGLYPH_FORMAT_R16G16B16_FLOAT    "R16G16B16_FLOAT"
#define VGLYPH_FORMAT_R16G16B16A16_FLOAT "R16G16B16A16_FLOAT"
#define VGLYPH_FORMAT_R32_FLOAT          "R32_FLOAT"
#define VGLYPH_FORMAT_R32G32_FLOAT       "R32G32_FLOAT"
#define VGLYPH_FORMAT_R32G32B32_FLOAT    "R32G32B32_FLOAT"
#define VGLYPH_FORMAT_R32G32B32A32_FLOAT "R32G32B32A32_FLOAT"
#define VGLYPH_FORMAT_R64_FLOAT          "R64_FLOAT"
#define VGLYPH_FORMAT_R64G64_FLOAT       "R64G64_FLOAT"
#define VGLYPH_FORMAT_R64G64B64_FLOAT    "R64G64B64_FLOAT"
#define VGLYPH_FORMAT_R64G64B64A64_FLOAT "R64G64B64A64_FLOAT"

typedef enum _vglyph_state
{
    VGLYPH_STATE_SUCCESS        = 0,
    VGLYPH_STATE_OUT_OF_MEMORY  = 1,
    VGLYPH_STATE_INVALID_CAST   = 2,
    VGLYPH_STATE_INVALID_FORMAT = 3
} vglyph_state_t;

typedef enum _vglyph_coordinate
{
    VGLYPH_COORDINATE_ABSOLUTE = 0,
    VGLYPH_COORDINATE_RELATIVE = 1
} vglyph_coordinate_t;

typedef enum _vglyph_alignment
{
    VGLYPH_ALIGNMENT_UNKNOWN = 0,
    VGLYPH_ALIGNMENT_1       = 1,
    VGLYPH_ALIGNMENT_2       = 2,
    VGLYPH_ALIGNMENT_4       = 4,
    VGLYPH_ALIGNMENT_8       = 8
} vglyph_alignment_t;

typedef enum _vglyph_endianness
{
    VGLYPH_ENDIANNESS_HOST   = 0,
    VGLYPH_ENDIANNESS_BIG    = 1,
    VGLYPH_ENDIANNESS_LITTLE = 2,
} vglyph_endianness_t;

typedef enum _vglyph_component
{
    VGLYPH_COMPONENT_ZERO  = 0,
    VGLYPH_COMPONENT_ONE   = 1,
    VGLYPH_COMPONENT_RED   = 2,
    VGLYPH_COMPONENT_GREEN = 3,
    VGLYPH_COMPONENT_BLUE  = 4,
    VGLYPH_COMPONENT_ALPHA = 5
} vglyph_component_t;

typedef enum _vglyph_rgba_float_size
{
    VGLYPH_RGBA_FLOAT_SIZE_0  = 0,
    VGLYPH_RGBA_FLOAT_SIZE_16 = 16,
    VGLYPH_RGBA_FLOAT_SIZE_32 = 32,
    VGLYPH_RGBA_FLOAT_SIZE_64 = 64
} vglyph_rgba_float_size_t;

typedef enum _vglyph_multisampling
{
    VGLYPH_MULTISAMPLING_DEFAULT = 0,
    VGLYPH_MULTISAMPLING_1       = 1,
    VGLYPH_MULTISAMPLING_2       = 2,
    VGLYPH_MULTISAMPLING_4       = 4,
    VGLYPH_MULTISAMPLING_8       = 8,
    VGLYPH_MULTISAMPLING_16      = 16,
    VGLYPH_MULTISAMPLING_32      = 32
} vglyph_multisampling_t;

typedef struct _vglyph_point
{
    vglyph_float32_t x;
    vglyph_float32_t y;
} vglyph_point_t;

typedef struct _vglyph_color
{
    vglyph_float64_t red;
    vglyph_float64_t green;
    vglyph_float64_t blue;
    vglyph_float64_t alpha;
} vglyph_color_t;

typedef struct _vglyph_packaging_bytes
{
    vglyph_uint32_t     byte_count;
    vglyph_endianness_t endianness;
} vglyph_packaging_bytes_t;

typedef struct _vglyph_rgba_components
{
    vglyph_component_t r;
    vglyph_component_t g;
    vglyph_component_t b;
    vglyph_component_t a;
} vglyph_rgba_components_t;

typedef struct _vglyph_rgba_uint_bit_count
{
    vglyph_uint8_t r;
    vglyph_uint8_t g;
    vglyph_uint8_t b;
    vglyph_uint8_t a;
} vglyph_rgba_uint_bit_count_t;

typedef struct _vglyph_rgba_float_bit_count
{
    vglyph_rgba_float_size_t r;
    vglyph_rgba_float_size_t g;
    vglyph_rgba_float_size_t b;
    vglyph_rgba_float_size_t a;
} vglyph_rgba_float_bit_count_t;

vglyph_public vglyph_uint32_t
vglyph_version(void);

vglyph_public const char*
vglyph_version_string(void);

vglyph_public vglyph_bool_t
vglyph_is_version_compatible(vglyph_uint32_t compile_version);

vglyph_public const char*
vglyph_state_to_string(vglyph_state_t state);

vglyph_public vglyph_type_t*
vglyph_get_object_type(void);

vglyph_public vglyph_type_t*
vglyph_get_type_type(void);

vglyph_public vglyph_type_t*
vglyph_get_figure_type(void);

vglyph_public vglyph_type_t*
vglyph_get_glyph_type(void);

vglyph_public vglyph_type_t*
vglyph_get_format_type(void);

vglyph_public vglyph_type_t*
vglyph_get_rgba_uint_format_type(void);

//vglyph_public vglyph_type_t*
//vglyph_get_rgba_float_format_type(void);

vglyph_public vglyph_type_t*
vglyph_get_transform_type(void);

vglyph_public vglyph_type_t*
vglyph_get_surface_type(void);

vglyph_public vglyph_object_t*
vglyph_object_reference(vglyph_object_t* object);

vglyph_public void
vglyph_object_destroy(vglyph_object_t* object);

vglyph_public vglyph_sint32_t
vglyph_object_get_reference_count(vglyph_object_t* object);

vglyph_public vglyph_state_t
vglyph_object_get_state(vglyph_object_t* object);

vglyph_public void
vglyph_object_reset_state(vglyph_object_t* object);

vglyph_public vglyph_type_t*
vglyph_object_get_type(vglyph_object_t* object);

vglyph_public vglyph_bool_t
vglyph_object_is_cast(vglyph_object_t* object, 
                      vglyph_type_t* type);

vglyph_public vglyph_type_t*
vglyph_object_to_type(vglyph_object_t* object);

vglyph_public vglyph_figure_t*
vglyph_object_to_figure(vglyph_object_t* object);

vglyph_public vglyph_glyph_t*
vglyph_object_to_glyph(vglyph_object_t* object);

vglyph_public vglyph_format_t*
vglyph_object_to_format(vglyph_object_t* object);

vglyph_public vglyph_rgba_uint_format_t*
vglyph_object_to_rgba_uint_format(vglyph_object_t* object);

//vglyph_public vglyph_rgba_float_format_t*
//vglyph_object_to_rgba_float_format(vglyph_object_t* object);

vglyph_public vglyph_transform_t*
vglyph_object_to_transform(vglyph_object_t* object);

vglyph_public vglyph_surface_t*
vglyph_object_to_surface(vglyph_object_t* object);

vglyph_public vglyph_object_t*
vglyph_type_to_object(vglyph_type_t* type);

vglyph_public vglyph_bool_t
vglyph_type_is_type(vglyph_type_t* type,
                    vglyph_type_t* equal_type);

vglyph_public vglyph_figure_t*
vglyph_figure_create(void);

vglyph_public vglyph_object_t*
vglyph_figure_to_object(vglyph_figure_t* figure);

vglyph_public vglyph_bool_t
vglyph_figure_draw_clear(vglyph_figure_t* figure);

vglyph_public vglyph_bool_t
vglyph_figure_draw_closepath(vglyph_figure_t* figure);

vglyph_public vglyph_bool_t
vglyph_figure_draw_moveto(vglyph_figure_t* figure,
                          vglyph_coordinate_t coordinate,
                          const vglyph_point_t* point);

vglyph_public vglyph_bool_t
vglyph_figure_draw_lineto(vglyph_figure_t* figure,
                          vglyph_coordinate_t coordinate,
                          const vglyph_point_t* point);

vglyph_public vglyph_bool_t
vglyph_figure_draw_curveto_cubic(vglyph_figure_t* figure,
                                 vglyph_coordinate_t coordinate,
                                 const vglyph_point_t* point,
                                 const vglyph_point_t* point1,
                                 const vglyph_point_t* point2);

vglyph_public vglyph_bool_t
vglyph_figure_draw_curveto_quadratic(vglyph_figure_t* figure,
                                     vglyph_coordinate_t coordinate,
                                     const vglyph_point_t* point,
                                     const vglyph_point_t* point1);

vglyph_public vglyph_bool_t
vglyph_figure_draw_arc(vglyph_figure_t* figure,
                       vglyph_coordinate_t coordinate,
                       const vglyph_point_t* point,
                       const vglyph_point_t* radius,
                       vglyph_float32_t angle,
                       vglyph_bool_t large_arc_flag,
                       vglyph_bool_t sweep_flag);

vglyph_public vglyph_bool_t
vglyph_figure_draw_lineto_horizontal(vglyph_figure_t* figure,
                                     vglyph_coordinate_t coordinate,
                                     vglyph_float32_t x);

vglyph_public vglyph_bool_t
vglyph_figure_draw_lineto_vertical(vglyph_figure_t* figure,
                                   vglyph_coordinate_t coordinate,
                                   vglyph_float32_t y);

vglyph_public vglyph_bool_t
vglyph_figure_draw_curveto_cubic_smooth(vglyph_figure_t* figure,
                                        vglyph_coordinate_t coordinate,
                                        const vglyph_point_t* point,
                                        const vglyph_point_t* point2);

vglyph_public vglyph_bool_t
vglyph_figure_draw_curveto_quadratic_smooth(vglyph_figure_t* figure,
                                            vglyph_coordinate_t coordinate,
                                            const vglyph_point_t* point);

vglyph_public vglyph_glyph_t*
vglyph_glyph_create(vglyph_figure_t* figure);

vglyph_public vglyph_object_t*
vglyph_glyph_to_object(vglyph_glyph_t* glyph);

vglyph_public vglyph_figure_t*
vglyph_glyph_get_figure(vglyph_glyph_t* glyph);

vglyph_public vglyph_float32_t
vglyph_glyph_get_width(vglyph_glyph_t* glyph);

vglyph_public vglyph_float32_t
vglyph_glyph_get_height(vglyph_glyph_t* glyph);

vglyph_public vglyph_float32_t
vglyph_glyph_get_horizontal_bearing_x(vglyph_glyph_t* glyph);

vglyph_public void
vglyph_glyph_set_horizontal_bearing_x(vglyph_glyph_t* glyph,
                                      vglyph_float32_t bearing_x);

vglyph_public vglyph_float32_t
vglyph_glyph_get_horizontal_bearing_y(vglyph_glyph_t* glyph);

vglyph_public void
vglyph_glyph_set_horizontal_bearing_y(vglyph_glyph_t* glyph,
                                      vglyph_float32_t bearing_y);

vglyph_public vglyph_float32_t
vglyph_glyph_get_horizontal_advance(vglyph_glyph_t* glyph);

vglyph_public void
vglyph_glyph_set_horizontal_advance(vglyph_glyph_t* glyph,
                                    vglyph_float32_t advance);

vglyph_public vglyph_float32_t
vglyph_glyph_get_vertical_bearing_x(vglyph_glyph_t* glyph);

vglyph_public void
vglyph_glyph_set_vertical_bearing_x(vglyph_glyph_t* glyph,
                                    vglyph_float32_t bearing_x);

vglyph_public vglyph_float32_t
vglyph_glyph_get_vertical_bearing_y(vglyph_glyph_t* glyph);

vglyph_public void
vglyph_glyph_set_vertical_bearing_y(vglyph_glyph_t* glyph,
                                    vglyph_float32_t bearing_y);

vglyph_public vglyph_float32_t
vglyph_glyph_get_vertical_advance(vglyph_glyph_t* glyph);

vglyph_public void
vglyph_glyph_set_vertical_advance(vglyph_glyph_t* glyph,
                                  vglyph_float32_t advance);

//vglyph_public vglyph_format_t*
//vglyph_format_create(const char* format);

vglyph_public vglyph_object_t*
vglyph_format_to_object(vglyph_format_t* format);

vglyph_public vglyph_rgba_uint_format_t*
vglyph_format_to_rgba_uint_format(vglyph_format_t* format);

//vglyph_public vglyph_rgba_float_format_t*
//vglyph_format_to_rgba_float_format(vglyph_format_t* format);

vglyph_public vglyph_uint32_t
vglyph_format_get_bits_per_pixel(vglyph_format_t* format);

vglyph_public void
vglyph_format_get_packaging_bytes(vglyph_format_t* format,
                                  vglyph_packaging_bytes_t* packaging_bytes);

vglyph_public vglyph_rgba_uint_format_t*
vglyph_rgba_uint_format_create(const vglyph_packaging_bytes_t* packaging_bytes,
                               const vglyph_rgba_components_t* components,
                               const vglyph_rgba_uint_bit_count_t* bit_count);

vglyph_public vglyph_object_t*
vglyph_rgba_uint_format_to_object(vglyph_rgba_uint_format_t* format);

vglyph_public vglyph_format_t*
vglyph_rgba_uint_format_to_format(vglyph_rgba_uint_format_t* format);

vglyph_public void
vglyph_rgba_uint_format_get_components(vglyph_rgba_uint_format_t* format,
                                       vglyph_rgba_components_t* components);

vglyph_public void
vglyph_rgba_uint_format_get_bit_count(vglyph_rgba_uint_format_t* format,
                                      vglyph_rgba_uint_bit_count_t* bit_count);

//vglyph_public vglyph_rgba_float_format_t*
//vglyph_rgba_float_format_create(const vglyph_rgba_components_t* components,
//                                const vglyph_rgba_float_bit_count_t* bit_components);

//vglyph_public vglyph_object_t*
//vglyph_rgba_float_format_to_object(vglyph_rgba_float_format_t* format);

//vglyph_public vglyph_format_t*
//vglyph_rgba_float_format_to_format(vglyph_rgba_float_format_t* format);

vglyph_public vglyph_transform_t*
vglyph_transform_create();

vglyph_public vglyph_transform_t*
vglyph_transform_create_copy(vglyph_transform_t* transform);

vglyph_public vglyph_object_t*
vglyph_transform_to_object(vglyph_transform_t* transform);

vglyph_public void
vglyph_transform_clear(vglyph_transform_t* transform);

vglyph_public void
vglyph_transform_combine(vglyph_transform_t* transform,
                         vglyph_transform_t* value);

vglyph_public void
vglyph_transform_translate(vglyph_transform_t* transform,
                           vglyph_float32_t x,
                           vglyph_float32_t y);

vglyph_public void
vglyph_transform_scale(vglyph_transform_t* transform,
                       vglyph_float32_t sx,
                       vglyph_float32_t sy);

vglyph_public void
vglyph_transform_rotate(vglyph_transform_t* transform,
                        vglyph_float32_t angle);

vglyph_public void
vglyph_transform_transform_point(vglyph_transform_t* transform,
                                 vglyph_point_t* point);

vglyph_public vglyph_uint32_t
vglyph_surface_get_data_size(vglyph_format_t* format,
                             vglyph_uint32_t width,
                             vglyph_uint32_t height,
                             vglyph_alignment_t row_alignment);

vglyph_public vglyph_surface_t*
vglyph_surface_create(vglyph_format_t* format,
                      vglyph_uint32_t width,
                      vglyph_uint32_t height,
                      vglyph_alignment_t row_alignment);

vglyph_public vglyph_surface_t*
vglyph_surface_create_for_data(vglyph_uint8_t* data,
                               vglyph_uint32_t data_size,
                               vglyph_format_t* format,
                               vglyph_uint32_t width,
                               vglyph_uint32_t height,
                               vglyph_alignment_t row_alignment);

vglyph_public vglyph_object_t*
vglyph_surface_to_object(vglyph_surface_t* surface);

vglyph_public vglyph_format_t*
vglyph_surface_get_format(vglyph_surface_t* surface);

vglyph_public vglyph_uint32_t
vglyph_surface_get_width(vglyph_surface_t* surface);

vglyph_public vglyph_uint32_t
vglyph_surface_get_height(vglyph_surface_t* surface);

vglyph_public vglyph_uint32_t
vglyph_surface_get_pitch(vglyph_surface_t* surface);

vglyph_public vglyph_multisampling_t
vglyph_surface_get_multisampling(vglyph_surface_t* surface);

vglyph_public void
vglyph_surface_set_multisampling(vglyph_surface_t* surface,
                                 vglyph_multisampling_t quality);

vglyph_public vglyph_uint8_t*
vglyph_surface_lock(vglyph_surface_t* surface,
                    vglyph_uint32_t x,
                    vglyph_uint32_t y,
                    vglyph_uint32_t width,
                    vglyph_uint32_t height);

vglyph_public void
vglyph_surface_unlock(vglyph_surface_t* surface);

vglyph_public void
vglyph_surface_fill(vglyph_surface_t* surface,
                    vglyph_uint32_t x,
                    vglyph_uint32_t y,
                    vglyph_uint32_t width,
                    vglyph_uint32_t height,
                    const vglyph_color_t* color);

vglyph_public void
vglyph_surface_get_pixel(vglyph_surface_t* surface,
                         vglyph_sint32_t x,
                         vglyph_sint32_t y,
                         vglyph_color_t* color);

vglyph_public void
vglyph_surface_set_pixel(vglyph_surface_t* surface,
                         vglyph_sint32_t x,
                         vglyph_sint32_t y,
                         const vglyph_color_t* color);

vglyph_public vglyph_bool_t
vglyph_surface_draw_glyph(vglyph_surface_t* surface,
                          vglyph_glyph_t* glyph,
                          vglyph_float32_t pt,
                          const vglyph_color_t* color,
                          const vglyph_point_t* position,
                          const vglyph_point_t* origin,
                          const vglyph_point_t* scale,
                          vglyph_float32_t angle);

vglyph_public vglyph_bool_t
vglyph_surface_draw_glyph_viewport(vglyph_surface_t* surface,
                                   vglyph_glyph_t* glyph,
                                   const vglyph_color_t* color,
                                   const vglyph_point_t* position,
                                   const vglyph_point_t* viewport,
                                   const vglyph_point_t* origin,
                                   vglyph_float32_t angle,
                                   vglyph_bool_t fit_to_viewport);

vglyph_public vglyph_bool_t
vglyph_surface_draw_glyph_transform(vglyph_surface_t* surface,
                                    vglyph_glyph_t* glyph,
                                    const vglyph_color_t* color,
                                    const vglyph_transform_t* transform);

VGLYPH_END

#endif
