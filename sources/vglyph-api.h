/* vglyph - library for visualize glyphs
 *
 * File: vglyph-api.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_API_H
#define VGLYPH_API_H

#include <assert.h>
#include <stdlib.h>

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

#endif
