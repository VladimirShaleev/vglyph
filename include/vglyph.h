/* vglyph - library for visualize glyphs
 *
 * File: vglyph.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_H
#define VGLYPH_H

#include "vglyph-config.h"

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

#ifdef __cplusplus
# define VGLYPH_BEGIN extern "C" {
# define VGLYPH_END   }
#else
# define VGLYPH_BEGIN
# define VGLYPH_END
#endif

#ifndef vglyph_public
# if defined (_MSC_VER) && !defined (VGLYPH_STATIC_BUILD)
#  define vglyph_public __declspec(dllimport)
# else
#  define vglyph_public
# endif
#endif

VGLYPH_BEGIN

typedef struct _vglyph_object            vglyph_object_t;
typedef struct _vglyph_type              vglyph_type_t;
typedef struct _vglyph_figure            vglyph_figure_t;
typedef struct _vglyph_format            vglyph_format_t;
typedef struct _vglyph_rgba_uint_format  vglyph_rgba_uint_format_t;
typedef struct _vglyph_rgba_float_format vglyph_rgba_float_format_t;
typedef struct _vglyph_surface           vglyph_surface_t;
typedef int                              vglyph_bool_t;
typedef float                            vglyph_float32_t;

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
    VGLYPH_STATE_SUCCESS       = 0,
    VGLYPH_STATE_OUT_OF_MEMORY = 1,
    VGLYPH_STATE_INVALID_CAST  = 2
} vglyph_state_t;

typedef enum _vglyph_hinting
{
    VGLYPH_HINTING_NONE       = 0x0,
    VGLYPH_HINTING_HORIZONTAL = 0x1,
    VGLYPH_HINTING_VERTICAL   = 0x2,
    VGLYPH_HINTING_ALL        = VGLYPH_HINTING_HORIZONTAL | VGLYPH_HINTING_VERTICAL
} vglyph_hinting_t;

typedef enum _vglyph_coordinate
{
    VGLYPH_COORDINATE_ABSOLUTE = 0,
    VGLYPH_COORDINATE_RELATIVE = 1
} vglyph_coordinate_t;

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

typedef struct _vglyph_point
{
    vglyph_float32_t x;
    vglyph_float32_t y;
    vglyph_hinting_t hinting;
} vglyph_point_t;

typedef struct _vglyph_rgba_components
{
    vglyph_component_t r;
    vglyph_component_t g;
    vglyph_component_t b;
    vglyph_component_t a;
} vglyph_rgba_components_t;

typedef struct _vglyph_rgba_uint_bit_count
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} vglyph_rgba_uint_bit_count_t;

typedef struct _vglyph_rgba_float_bit_count
{
    vglyph_rgba_float_size_t r;
    vglyph_rgba_float_size_t g;
    vglyph_rgba_float_size_t b;
    vglyph_rgba_float_size_t a;
} vglyph_rgba_float_bit_count_t;

vglyph_public int
vglyph_version(void);

vglyph_public const char*
vglyph_version_string(void);

vglyph_public vglyph_bool_t
vglyph_is_version_compatible(int compile_version);

vglyph_public const char*
vglyph_state_to_string(vglyph_state_t state);

vglyph_public vglyph_object_t*
vglyph_object_reference(vglyph_object_t* object);

vglyph_public void
vglyph_object_destroy(vglyph_object_t* object);

vglyph_public int
vglyph_object_get_reference_count(vglyph_object_t* object);

vglyph_public vglyph_state_t
vglyph_object_get_state(vglyph_object_t* object);

vglyph_public vglyph_figure_t*
vglyph_object_to_figure(vglyph_object_t* object);

vglyph_public vglyph_format_t*
vglyph_object_to_format(vglyph_object_t* object);

vglyph_public vglyph_rgba_uint_format_t*
vglyph_object_to_rgba_uint_format(vglyph_object_t* object);

//vglyph_public vglyph_rgba_float_format_t*
//vglyph_object_to_rgba_float_format(vglyph_object_t* object);

vglyph_public vglyph_surface_t*
vglyph_object_to_surface(vglyph_object_t* object);

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
                                     vglyph_float32_t x,
                                     vglyph_hinting_t hinting);

vglyph_public vglyph_bool_t
vglyph_figure_draw_lineto_vertical(vglyph_figure_t* figure,
                                   vglyph_coordinate_t coordinate,
                                   vglyph_float32_t y,
                                   vglyph_hinting_t hinting);

//vglyph_public vglyph_format_t*
//vglyph_format_create(const char* format);

vglyph_public vglyph_object_t*
vglyph_format_to_object(vglyph_format_t* format);

vglyph_public vglyph_rgba_uint_format_t*
vglyph_format_to_rgba_uint_format(vglyph_format_t* format);

//vglyph_public vglyph_rgba_float_format_t*
//vglyph_format_to_rgba_float_format(vglyph_format_t* format);

vglyph_public vglyph_rgba_uint_format_t*
vglyph_rgba_uint_format_create(const vglyph_rgba_components_t* components,
                               const vglyph_rgba_uint_bit_count_t* bit_count);

vglyph_public vglyph_object_t*
vglyph_rgba_uint_format_to_object(vglyph_rgba_uint_format_t* format);

vglyph_public vglyph_format_t*
vglyph_rgba_uint_format_to_format(vglyph_rgba_uint_format_t* format);

//vglyph_public vglyph_rgba_float_format_t*
//vglyph_rgba_float_format_create(const vglyph_rgba_components_t* components,
//                                const vglyph_rgba_float_bit_count_t* bit_components);

//vglyph_public vglyph_object_t*
//vglyph_rgba_float_format_to_object(vglyph_rgba_float_format_t* format);

//vglyph_public vglyph_format_t*
//vglyph_rgba_float_format_to_format(vglyph_rgba_float_format_t* format);

//vglyph_public vglyph_surface_t*
//vglyph_surface_create(const vglyph_format_t* format,
//                      unsigned int width,
//                      unsigned int height);

vglyph_public vglyph_surface_t*
vglyph_surface_create_for_data(unsigned char* data,
                               const vglyph_format_t* format,
                               unsigned int width,
                               unsigned int height);

vglyph_public vglyph_object_t*
vglyph_surface_to_object(vglyph_surface_t* surface);

VGLYPH_END

#endif
