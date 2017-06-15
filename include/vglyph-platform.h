/* vglyph - library for visualize glyphs
 *
 * File: vglyph-platform.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_PLATFORM_H
#define VGLYPH_PLATFORM_H

#include <stdint.h>

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

typedef int32_t  _vglyph_bool;
typedef int8_t   _vglyph_sint8;
typedef uint8_t  _vglyph_uint8;
typedef int16_t  _vglyph_sint16;
typedef uint16_t _vglyph_uint16;
typedef int32_t  _vglyph_sint32;
typedef uint32_t _vglyph_uint32;
typedef float    _vglyph_float32;

#endif
