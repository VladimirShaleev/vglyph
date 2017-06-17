/* vglyph - library for visualize glyphs
 *
 * File: vglyph-types.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_TYPES_H
#define VGLYPH_TYPES_H

#ifndef FALSE
# define FALSE 0
#endif

#ifndef TRUE
# define TRUE 1
#endif

#ifdef VGLYPH_NO_STDINT_H
# include <stddef.h>
  typedef ptrdiff_t vglyph_sint_t;
  typedef size_t    vglyph_uint_t;
#else
# include <stdint.h>
  typedef intptr_t  vglyph_sint_t;
  typedef uintptr_t vglyph_uint_t;
#endif

#endif
