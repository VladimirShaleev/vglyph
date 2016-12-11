/* vglyph - library for visualize glyphs
 *
 * File: vglyph.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_H
#define VGLYPH_H

#include "vglyph-config.h"

#define VGLYPH_VERSION_MAJON  1
#define VGLYPH_VERSION_MINOR  0
#define VGLYPH_VERSION_MICRO  0

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

typedef struct _vglyph_object  vglyph_object_t;
typedef struct _vglyph_figure  vglyph_figure_t;
typedef int                    vglyph_bool_t;
typedef float                  vglyph_float32_t;

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
    VGLYPH_HINTING_VERTICAL   = 0x2
} vglyph_hinting_t;

typedef enum _vglyph_coordinate
{
    VGLYPH_COORDINATE_ABSOLUTE = 0,
    VGLYPH_COORDINATE_RELATIVE = 1
} vglyph_coordinate_t;

typedef struct _vglyph_point
{
    vglyph_float32_t x;
    vglyph_float32_t y;
    vglyph_hinting_t hinting;
} vglyph_point_t;

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
vglyph_figure_create(void);

vglyph_public vglyph_figure_t*
vglyph_figure_reference(vglyph_figure_t* figure);

vglyph_public void
vglyph_figure_destroy(vglyph_figure_t* figure);

vglyph_public int
vglyph_figure_get_reference_count(vglyph_figure_t* figure);

vglyph_public vglyph_state_t
vglyph_figure_get_state(vglyph_figure_t* figure);

vglyph_public vglyph_object_t*
vglyph_figure_figure_to_object(vglyph_figure_t* figure);

vglyph_public vglyph_figure_t*
vglyph_figure_object_to_figure(vglyph_object_t* object);

vglyph_public vglyph_bool_t
vglyph_figure_draw_clear(vglyph_figure_t* figure);

vglyph_public vglyph_bool_t
vglyph_figure_draw_closepath(vglyph_figure_t* figure);

vglyph_public vglyph_bool_t
vglyph_figure_draw_moveto(vglyph_figure_t* figure,
                          vglyph_coordinate_t coordinate,
                          vglyph_point_t* point);

vglyph_public vglyph_bool_t
vglyph_figure_draw_lineto(vglyph_figure_t* figure,
                          vglyph_coordinate_t coordinate,
                          vglyph_point_t* point);

vglyph_public vglyph_bool_t
vglyph_figure_draw_curveto_cubic(vglyph_figure_t* figure,
                                 vglyph_coordinate_t coordinate,
                                 vglyph_point_t* point,
                                 vglyph_point_t* point1,
                                 vglyph_point_t* point2);

vglyph_public vglyph_bool_t
vglyph_figure_draw_curveto_quadratic(vglyph_figure_t* figure,
                                     vglyph_coordinate_t coordinate,
                                     vglyph_point_t* point,
                                     vglyph_point_t* point1);

vglyph_public vglyph_bool_t
vglyph_figure_draw_arc(vglyph_figure_t* figure,
                       vglyph_coordinate_t coordinate,
                       vglyph_point_t* point,
                       vglyph_point_t* radius,
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

VGLYPH_END

#endif
