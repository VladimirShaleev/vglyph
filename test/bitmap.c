/* vglyph-test - test library for visualize glyphs
 *
 * File: bitmap.c
 * Copyright (C) 2017 Shaleev Vladimir
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bitmap.h"

#ifndef FALSE
# define FALSE 0
#endif

#ifndef TRUE
# define TRUE 1
#endif

typedef enum _bitmap_compression
{
    BITMAP_COMPRESSION_RGB       = 0,
    BITMAP_COMPRESSION_RLE8      = 1,
    BITMAP_COMPRESSION_RLE4      = 2,
    BITMAP_COMPRESSION_BITFIELDS = 3,
    BITMAP_COMPRESSION_JPEG      = 4,
    BITMAP_COMPRESSION_PNG       = 5
} bitmap_compression_t;

typedef struct _bitmap_header
{
    vglyph_uint32_t size;
    vglyph_uint16_t reserved1;
    vglyph_uint16_t reserved2;
    vglyph_uint32_t offset_bits;
} bitmap_header_t;

typedef struct _bitmap_ciexyz
{
    vglyph_sint32_t ciexyz_x;
    vglyph_sint32_t ciexyz_y;
    vglyph_sint32_t ciexyz_z;
} bitmap_ciexyz_t;

typedef struct _bitmap_ciexyztriple {
    bitmap_ciexyz_t ciexyz_red;
    bitmap_ciexyz_t ciexyz_green;
    bitmap_ciexyz_t ciexyz_blue;
} bitmap_ciexyztriple_t;

typedef struct _bitmap_info_core
{
    vglyph_uint32_t size;
    vglyph_uint16_t width;
    vglyph_uint16_t height;
    vglyph_uint16_t planes;
    vglyph_uint16_t bit_count;
} bitmap_info_core_t;

typedef struct _bitmap_info_3 
{
    vglyph_uint32_t size;
    vglyph_sint32_t width;
    vglyph_sint32_t height;
    vglyph_uint16_t planes;
    vglyph_uint16_t bit_count;
    vglyph_uint32_t compression;
    vglyph_uint32_t size_image;
    vglyph_sint32_t x_pels_per_meter;
    vglyph_sint32_t y_pels_per_meter;
    vglyph_uint32_t clr_used;
    vglyph_uint32_t clr_important;
} bitmap_info_3_t;

typedef struct _bitmap_info_4 
{
    vglyph_uint32_t       size;
    vglyph_sint32_t       width;
    vglyph_sint32_t       height;
    vglyph_uint16_t       planes;
    vglyph_uint16_t       bit_count;
    vglyph_uint32_t       compression;
    vglyph_uint32_t       size_image;
    vglyph_sint32_t       x_pels_per_meter;
    vglyph_sint32_t       y_pels_per_meter;
    vglyph_uint32_t       clr_used;
    vglyph_uint32_t       clr_important;
    vglyph_uint32_t       redMask;
    vglyph_uint32_t       greenMask;
    vglyph_uint32_t       blueMask;
    vglyph_uint32_t       alphaMask;
    vglyph_uint32_t       cs_type;
    bitmap_ciexyztriple_t end_points;
    vglyph_uint32_t       gamma_red;
    vglyph_uint32_t       gamma_green;
    vglyph_uint32_t       gamma_blue;
} bitmap_info_4_t;

vglyph_bool_t 
bitmap_save(vglyph_surface_t* surface, 
            const char* name)
{
    if (vglyph_object_get_state(vglyph_surface_to_object(surface)) != VGLYPH_STATE_SUCCESS)
        return FALSE;

    const vglyph_uint32_t width  = vglyph_surface_get_width(surface);
    const vglyph_uint32_t height = vglyph_surface_get_height(surface);
    const vglyph_uint32_t pitch  = vglyph_surface_get_pitch(surface);

    vglyph_format_t* format = vglyph_surface_get_format(surface);
    const vglyph_uint32_t bpp = vglyph_format_get_bits_per_pixel(format);
    const vglyph_uint32_t data_size = vglyph_surface_get_data_size(format, width, height, VGLYPH_ALIGNMENT_4);
    vglyph_object_destroy(vglyph_format_to_object(format));

    switch (bpp)
    {
        case 1:
        case 8:
        case 16:
        case 24:
        case 32:
        case 48:
        case 64:
            break;

        default:
            return FALSE;
    }

    const vglyph_uint32_t header_size = sizeof(bitmap_header_t);
    const vglyph_uint32_t info_size = sizeof(bitmap_info_3_t);

    vglyph_uint16_t type = 'MB';

    bitmap_header_t header;
    header.size        = 2 + header_size + info_size + data_size;
    header.reserved1   = 0;
    header.reserved2   = 0;
    header.offset_bits = 2 + header_size + info_size;

    bitmap_info_3_t info;
    info.size             = info_size;
    info.width            = (vglyph_sint32_t)width;
    info.height           = (vglyph_sint32_t)height;
    info.planes           = 1;
    info.bit_count        = (vglyph_uint16_t)bpp;
    info.compression      = BITMAP_COMPRESSION_RGB;
    info.size_image       = data_size;
    info.x_pels_per_meter = 0;
    info.y_pels_per_meter = 0;
    info.clr_used         = 0;
    info.clr_important    = 0;

    FILE* file = fopen(name, "wb");

    if (!file)
        return FALSE;

    vglyph_uint32_t write_pitch = (width * bpp + 7) >> 3;
    vglyph_uint32_t align = VGLYPH_ALIGNMENT_4 - 1;
    write_pitch = (pitch + align) & ~align;

    vglyph_uint32_t padding = write_pitch - pitch;
    uint8_t* data_padding = (uint8_t*)malloc(padding);
    memset(data_padding, 0, padding);

    vglyph_uint8_t* data = vglyph_surface_lock(surface, 0, 0, width, height);
    vglyph_bool_t result = TRUE;

    do
    {
        if (fwrite(&type, 1, 2, file) != 2 ||
            fwrite(&header, 1, header_size, file) != header_size ||
            fwrite(&info, 1, info_size, file) != info_size)
        {
            result = FALSE;
            break;
        }

        for (vglyph_uint32_t y = 0, offset = (height - 1) * pitch; y < height; ++y, offset -= pitch)
        {
            if (fwrite(data + offset, 1, pitch, file) != pitch)
            {
                result = FALSE;
                break;
            }

            if (fwrite(data_padding, 1, padding, file) != padding)
            {
                result = FALSE;
                break;
            }
        }

    } while (FALSE);

    vglyph_surface_unlock(surface);
    free(data_padding);
    fclose(file);

    return result;
}
