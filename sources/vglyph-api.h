/* vglyph - library for visualize glyphs
 *
 * File: vglyph-api.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_API_H
#define VGLYPH_API_H

#include <assert.h>
#include <stdlib.h>
#include <math.h>

#if defined (_MSC_VER) && !defined (VGLYPH_STATIC_BUILD)
# define vglyph_public __declspec(dllexport)
#endif

#if defined (_MSC_VER) && !defined (__cplusplus)
# undef inline
# define inline __inline
#endif

#ifdef __STRICT_ANSI__
# undef inline
# define inline __inline__
#endif

#include "vglyph.h"

static inline vglyph_bool_t
_vglyph_is_little_endian(void)
{
    const vglyph_uint32_t i = 1;
    return *((vglyph_uint8_t*)&i) == 1;
}

#endif
