/* vglyph - library for visualize glyphs
 *
 * File: vglyph-uuid.h
 * Copyright (C) 2016 Shaleev Vladimir
 */

#ifndef VGLYPH_UUID_H
#define VGLYPH_UUID_H

#include "vglyph-api.h"
#include "vglyph-types.h"

typedef struct _vglyph_uuid
{
    vglyph_uint32_t time_low;
    vglyph_uint16_t time_mid;
    vglyph_uint16_t time_hi_and_version;
    vglyph_uint8_t  clock_seq_hi_and_reserved;
    vglyph_uint8_t  clock_seq_low;
    vglyph_uint8_t  node[6];
} vglyph_uuid_t;

static inline vglyph_bool_t
_vglyph_uuid_equal(const vglyph_uuid_t* uuid1,
                   const vglyph_uuid_t* uuid2)
{
    const uint32_t* data1 = (const uint32_t*)((const void*)uuid1);
    const uint32_t* data2 = (const uint32_t*)((const void*)uuid2);

    return data1[0] == data2[0] &&
           data1[1] == data2[1] &&
           data1[2] == data2[2] &&
           data1[3] == data2[3];
}

#endif
