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

#define MAKE_FIXED_POINT(integer, fraction) (((integer & 0xFFFF) << 16) | (fraction & 0xFFFF))

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

static inline vglyph_uint32_t
bitmap_get_capacity(vglyph_uint32_t bit_count)
{
    if (!bit_count)
        return 0;

    const vglyph_uint32_t capacity = ~0;
    const vglyph_uint32_t shift = (sizeof(capacity) << 3) - bit_count;

    return capacity << shift >> shift;
}

static bitmap_info_core_t*
bitmap_info_alloc(vglyph_format_t* format,
                  vglyph_uint32_t width,
                  vglyph_uint32_t height,
                  vglyph_uint32_t data_size)
{
    typedef union _bitmap_info
    {
        bitmap_info_core_t* info_core;
        bitmap_info_3_t*    info_3;
        bitmap_info_4_t*    info_4;
    } bitmap_info_t;

    vglyph_rgba_uint_format_t* rgba_format = vglyph_format_to_rgba_uint_format(format);

    if (vglyph_object_get_state(vglyph_rgba_uint_format_to_object(rgba_format)))
        return NULL;

    vglyph_rgba_components_t components;
    vglyph_rgba_uint_bit_count_t bit_count;
    vglyph_rgba_uint_format_get_components(rgba_format, &components);
    vglyph_rgba_uint_format_get_bit_count(rgba_format, &bit_count);
    const vglyph_uint32_t bpp = vglyph_format_get_bits_per_pixel(format);

    vglyph_bool_t is_info_3 = FALSE;

    switch (bpp)
    {
        case 16:
            if (bit_count.r == 1 &&
                bit_count.g == 5 &&
                bit_count.b == 5 &&
                bit_count.a == 5)
                is_info_3 = TRUE;
            break;

        case 24:
            if ((bit_count.r == 0 || bit_count.r == 8) &&
                (bit_count.g == 0 || bit_count.g == 8) &&
                (bit_count.b == 0 || bit_count.b == 8) &&
                (bit_count.a == 0 || bit_count.a == 8) &&
                (bit_count.r + bit_count.g + bit_count.b + bit_count.a == 24))
                is_info_3 = TRUE;
            break;

        case 32:
            if ((bit_count.r == 0 || bit_count.r == 8) &&
                (bit_count.g == 0 || bit_count.g == 8) &&
                (bit_count.b == 0 || bit_count.b == 8) &&
                (bit_count.a == 0 || bit_count.a == 8) &&
                (bit_count.r + bit_count.g + bit_count.b + bit_count.a == 32))
                is_info_3 = TRUE;
            break;
    }

    bitmap_info_t result;
    vglyph_uint32_t info_size;

    if (is_info_3)
        info_size = sizeof(bitmap_info_3_t);
    else 
        info_size = sizeof(bitmap_info_4_t);

    result.info_core = (bitmap_info_core_t*)malloc(info_size);

    bitmap_info_3_t* info_3 = result.info_3;
    info_3->size             = info_size;
    info_3->width            = (vglyph_sint32_t)width;
    info_3->height           = (vglyph_sint32_t)height;
    info_3->planes           = 1;
    info_3->bit_count        = (vglyph_uint16_t)bpp;
    info_3->compression      = BITMAP_COMPRESSION_RGB;
    info_3->size_image       = data_size;
    info_3->x_pels_per_meter = 0;
    info_3->y_pels_per_meter = 0;
    info_3->clr_used         = 0;
    info_3->clr_important    = 0;

    if (!is_info_3)
    {
        bitmap_info_4_t* info_4 = result.info_4;

        const vglyph_uint32_t blue_shift  = 0;
        const vglyph_uint32_t green_shift = bit_count.b;
        const vglyph_uint32_t red_shift   = bit_count.g + green_shift;
        const vglyph_uint32_t alpha_shift = bit_count.r + red_shift;

        const vglyph_uint32_t red_capacity   = bitmap_get_capacity(bit_count.r);
        const vglyph_uint32_t green_capacity = bitmap_get_capacity(bit_count.g);
        const vglyph_uint32_t blue_capacity  = bitmap_get_capacity(bit_count.b);
        const vglyph_uint32_t alpha_capacity = bitmap_get_capacity(bit_count.a);

        info_4->compression = BITMAP_COMPRESSION_BITFIELDS;
        info_4->redMask   = red_capacity   << red_shift;
        info_4->greenMask = green_capacity << green_shift;
        info_4->blueMask  = blue_capacity  << blue_shift;
        info_4->alphaMask = alpha_capacity << alpha_shift;
        info_4->cs_type   = 'sRGB';
        info_4->end_points.ciexyz_red.ciexyz_x   = MAKE_FIXED_POINT(0, 64);
        info_4->end_points.ciexyz_red.ciexyz_y   = MAKE_FIXED_POINT(0, 33);
        info_4->end_points.ciexyz_red.ciexyz_z   = MAKE_FIXED_POINT(0, 03);
        info_4->end_points.ciexyz_green.ciexyz_x = MAKE_FIXED_POINT(0, 30);
        info_4->end_points.ciexyz_green.ciexyz_y = MAKE_FIXED_POINT(0, 60);
        info_4->end_points.ciexyz_green.ciexyz_z = MAKE_FIXED_POINT(0, 10);
        info_4->end_points.ciexyz_blue.ciexyz_x  = MAKE_FIXED_POINT(0, 15);
        info_4->end_points.ciexyz_blue.ciexyz_y  = MAKE_FIXED_POINT(0, 06);
        info_4->end_points.ciexyz_blue.ciexyz_z  = MAKE_FIXED_POINT(0, 79);
        info_4->gamma_red   = MAKE_FIXED_POINT(2, 20);
        info_4->gamma_green = MAKE_FIXED_POINT(2, 20);
        info_4->gamma_blue  = MAKE_FIXED_POINT(2, 20);
    }

    return result.info_core;
}

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
    bitmap_info_core_t* info = bitmap_info_alloc(format, width, height, data_size);
    vglyph_object_destroy(vglyph_format_to_object(format));

    if (!info)
        return FALSE;

    switch (bpp)
    {
        //case 1:
        //case 2:
        //case 4:
        //case 8:
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
    const vglyph_uint16_t type = 'MB';

    bitmap_header_t header;
    header.size        = 2 + header_size + info->size + data_size;
    header.reserved1   = 0;
    header.reserved2   = 0;
    header.offset_bits = 2 + header_size + info->size;

    FILE* file = fopen(name, "wb");

    if (!file)
    {
        free(info);
        return FALSE;
    }

    vglyph_uint32_t write_pitch = (width * bpp + 7) >> 3;
    vglyph_uint32_t align = VGLYPH_ALIGNMENT_4 - 1;
    write_pitch = (pitch + align) & ~align;

    vglyph_uint32_t padding = write_pitch - pitch;
    uint8_t data_padding = 0;

    vglyph_uint8_t* data = vglyph_surface_lock(surface, 0, 0, width, height);
    vglyph_bool_t result = TRUE;

    do
    {
        if (fwrite(&type, 1, 2, file) != 2 ||
            fwrite(&header, 1, header_size, file) != header_size ||
            fwrite(info, 1, info->size, file) != info->size)
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

            for (vglyph_uint32_t i = 0; i < padding; ++i)
            {
                if (fwrite(&data_padding, 1, 1, file) != 1)
                {
                    result = FALSE;
                    break;
                }
            }
        }

    } while (FALSE);

    vglyph_surface_unlock(surface);
    fclose(file);
    free(info);

    return result;
}
