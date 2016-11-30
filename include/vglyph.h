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
typedef struct _vglyph_segment vglyph_segment_t;
typedef struct _vglyph_figure  vglyph_figure_t;
typedef int                    vglyph_bool_t;

typedef enum _vglyph_state
{
    VGLYPH_STATE_SUCCESS       = 0,
    VGLYPH_STATE_OUT_OF_MEMORY = 1,
    VGLYPH_STATE_INVALID_CAST  = 2
} vglyph_state_t;

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

vglyph_public vglyph_segment_t*
vglyph_segment_reference(vglyph_segment_t* segment);

vglyph_public void
vglyph_segment_destroy(vglyph_segment_t* segment);

vglyph_public int
vglyph_segment_get_reference_count(vglyph_segment_t* segment);

vglyph_public vglyph_state_t
vglyph_segment_get_state(vglyph_segment_t* segment);

vglyph_public vglyph_object_t*
vglyph_segment_segment_to_object(vglyph_segment_t* segment);

vglyph_public vglyph_segment_t*
vglyph_segment_object_to_segment(vglyph_object_t* object);

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

VGLYPH_END

#endif
