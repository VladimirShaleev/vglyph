/* vglyph - library for visualize glyphs
 *
 * File: vglyph-win32-platform.h
 * Copyright (C) 2018 Shaleev Vladimir
 */

#ifndef VGLYPH_WIN32_PLATFORM_H
#define VGLYPH_WIN32_PLATFORM_H

#include <Windows.h>

#include "../vglyph-api.h"

vglyph_uint_t
_vglyph_get_device_dpi(void)
{
    HDC hDC = GetDC(NULL);
    vglyph_uint_t dpi = (vglyph_uint_t)GetDeviceCaps(hDC, LOGPIXELSX);
    ReleaseDC(NULL, hDC);

    return dpi;
}

#endif
