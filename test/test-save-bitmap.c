/* vglyph-test - test library for visualize glyphs
 *
 * File: test-save-bitmap.c
 * Copyright (C) 2019 Shaleev Vladimir
 */

#include "test-save-bitmap.h"

static char app_dir[512] = { '\0' };

static int save_bitmap(const char* name,
                       vglyph_format_t* format, 
                       vglyph_uint32_t width, 
                       vglyph_uint32_t height)
{
    static char path[512] = { '\0' };
    strcpy(path, app_dir);
    strcat(path, name);

    vglyph_surface_t* surface = vglyph_surface_create(format, width, height, VGLYPH_ALIGNMENT_4);
    vglyph_float64_t inv_width = 1.0 / (width - 1);
    vglyph_float64_t inv_height = 1.0 / (height - 1);

    for (vglyph_uint32_t y = 0; y < height; ++y)
    {
        for (vglyph_uint32_t x = 0; x < width; ++x)
        {
            vglyph_color_t color = { x * inv_width, y * inv_height, 1.0, 1.0 };
            vglyph_surface_set_pixel(surface, x, y, &color);
        }
    }

    vglyph_bool_t result = bitmap_save(surface, path);

    vglyph_object_destroy(vglyph_surface_to_object(surface));

    return result ? 0 : 1;
}

static int test_save_bitmap_x1r5g5b5(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 2;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_LITTLE;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_ZERO;
    components.g = VGLYPH_COMPONENT_RED;
    components.b = VGLYPH_COMPONENT_GREEN;
    components.a = VGLYPH_COMPONENT_BLUE;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 1;
    bit_count.g = 5;
    bit_count.b = 5;
    bit_count.a = 5;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    int result = save_bitmap("x1r5g5b5.bmp", format, 200, 100);
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

static int test_save_bitmap_x4r4g4b4(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 2;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_LITTLE;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_ZERO;
    components.g = VGLYPH_COMPONENT_RED;
    components.b = VGLYPH_COMPONENT_GREEN;
    components.a = VGLYPH_COMPONENT_BLUE;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 4;
    bit_count.g = 4;
    bit_count.b = 4;
    bit_count.a = 4;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    int result = save_bitmap("x4r4g4b4.bmp", format, 200, 100);
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

static int test_save_bitmap_r5g6b5(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 2;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_LITTLE;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_RED;
    components.g = VGLYPH_COMPONENT_GREEN;
    components.b = VGLYPH_COMPONENT_BLUE;
    components.a = VGLYPH_COMPONENT_ZERO;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 5;
    bit_count.g = 6;
    bit_count.b = 5;
    bit_count.a = 0;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    int result = save_bitmap("r5g6b5.bmp", format, 200, 100);
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

static int test_save_bitmap_r8g8b8(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 3;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_LITTLE;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_ZERO;
    components.g = VGLYPH_COMPONENT_RED;
    components.b = VGLYPH_COMPONENT_GREEN;
    components.a = VGLYPH_COMPONENT_BLUE;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 0;
    bit_count.g = 8;
    bit_count.b = 8;
    bit_count.a = 8;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    int result = save_bitmap("r8g8b8.bmp", format, 200, 100);
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

int test_save_bitmap_run(const char* dir)
{
    strcpy(app_dir, dir);
    int result = 0;
    
    BEGIN_TESTS()
    ADD_TEST(test_save_bitmap_x1r5g5b5)
    ADD_TEST(test_save_bitmap_x4r4g4b4)
    ADD_TEST(test_save_bitmap_r5g6b5)
    ADD_TEST(test_save_bitmap_r8g8b8)
    END_TESTS(result)

    return result;
}
