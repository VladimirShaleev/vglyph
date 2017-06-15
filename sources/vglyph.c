/* vglyph - library for visualize glyphs
 *
 * File: vglyph.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph-api.h"
#include "vglyph-types.h"

vglyph_uint32_t
vglyph_version(void)
{
    return VGLYPH_VERSION;
}

const char*
vglyph_version_string(void)
{
    return VGLYPH_VERSION_STRING;
}

vglyph_bool_t
vglyph_is_version_compatible(vglyph_uint32_t compile_version)
{
    return (VGLYPH_VERSION >> 8) >= (compile_version >> 8) ? TRUE : FALSE;
}

const char*
vglyph_state_to_string(vglyph_state_t state)
{
    switch (state)
    {
        case VGLYPH_STATE_SUCCESS:
            return "no error has occurred";

        case VGLYPH_STATE_OUT_OF_MEMORY:
            return "out of memory";

        case VGLYPH_STATE_INVALID_CAST:
            return "invalid cast";
    }
    return "<unknown error state>";
}
