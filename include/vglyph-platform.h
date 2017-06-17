/* vglyph - library for visualize glyphs
 *
 * File: vglyph-platform.h
 * Copyright (C) 2017 Shaleev Vladimir
 */

#ifndef VGLYPH_PLATFORM_H
#define VGLYPH_PLATFORM_H

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

#ifndef VGLYPH_NO_STDINT_H
# if defined (_MSC_VER) && (_MSC_VER < 1600)
   typedef signed   __int8  int8_t;
   typedef unsigned __int8  uint8_t;
   typedef signed   __int16 int16_t;
   typedef unsigned __int16 uint16_t;
   typedef signed   __int32 int32_t;
   typedef unsigned __int32 uint32_t;
# else
#  include <stdint.h>
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
