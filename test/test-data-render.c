/* vglyph-test - test library for visualize glyphs
 *
 * File: test-data-render.c
 * Copyright (C) 2019 Shaleev Vladimir
 */

#include "test-data-render.h"

static int test_rgba_uint_data_render(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 1;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_BIG;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_RED;
    components.g = VGLYPH_COMPONENT_GREEN;
    components.b = VGLYPH_COMPONENT_BLUE;
    components.a = VGLYPH_COMPONENT_ALPHA;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 3;
    bit_count.g = 5;
    bit_count.b = 2;
    bit_count.a = 1;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    vglyph_uint32_t    width  = (vglyph_uint32_t)7;
    vglyph_uint32_t    height = (vglyph_uint32_t)1;
    vglyph_alignment_t align  = VGLYPH_ALIGNMENT_4;

    vglyph_surface_t* surface = vglyph_surface_create(format, width, height, align);

    vglyph_uint8_t* data = vglyph_surface_lock(surface, 0, 0, width, height);
    memset(data, 0, 12);
    vglyph_surface_unlock(surface);

    for (vglyph_uint32_t i = 0; i < 7; ++i)
    {
        vglyph_float64_t chanel = 1.0 / 6.0 * i;
        vglyph_color_t color = { chanel, chanel, chanel, chanel };

        vglyph_surface_set_pixel(surface, i, 0, &color);
    }

    vglyph_uint8_t test_data[12] = { 0x00, 0x04, 0xA9, 0x29, 0x48, 0x5B, 0x5B, 0xB5, 0xFF, 0xF8, 0x00, 0x00 };

    data = vglyph_surface_lock(surface, 0, 0, width, height);

    int result = memcmp(data, test_data, 12);

    vglyph_surface_unlock(surface);

    vglyph_object_destroy(vglyph_surface_to_object(surface));
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

static int test_rgba_uint16_data_render(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 1;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_BIG;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_RED;
    components.g = VGLYPH_COMPONENT_GREEN;
    components.b = VGLYPH_COMPONENT_ONE;
    components.a = VGLYPH_COMPONENT_ALPHA;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 5;
    bit_count.g = 6;
    bit_count.b = 5;
    bit_count.a = 0;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    vglyph_uint32_t    width  = (vglyph_uint32_t)3;
    vglyph_uint32_t    height = (vglyph_uint32_t)1;
    vglyph_alignment_t align  = VGLYPH_ALIGNMENT_4;

    vglyph_surface_t* surface = vglyph_surface_create(format, width, height, align);

    vglyph_uint8_t* data = vglyph_surface_lock(surface, 0, 0, width, height);
    memset(data, 0, 8);
    vglyph_surface_unlock(surface);

    for (vglyph_uint32_t i = 0; i < 3; ++i)
    {
        vglyph_float64_t chanel = 1.0 / 2.0 * i;
        vglyph_color_t color = { chanel, chanel, chanel, chanel };

        vglyph_surface_set_pixel(surface, i, 0, &color);
    }

    vglyph_uint8_t test_data[8] = {
        0x00, 0x1F,
        0x84, 0x1F,
        0xFF, 0xFF,
        0x00, 0x00
    };

    data = vglyph_surface_lock(surface, 0, 0, width, height);

    int result = memcmp(data, test_data, 8);

    vglyph_surface_unlock(surface);

    vglyph_object_destroy(vglyph_surface_to_object(surface));
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

static int test_rgba_uint32_data_render(void)
{
    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 1;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_BIG;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_BLUE;
    components.g = VGLYPH_COMPONENT_GREEN;
    components.b = VGLYPH_COMPONENT_RED;
    components.a = VGLYPH_COMPONENT_ALPHA;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 10;
    bit_count.g = 5;
    bit_count.b = 7;
    bit_count.a = 10;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    vglyph_uint32_t    width  = (vglyph_uint32_t)7;
    vglyph_uint32_t    height = (vglyph_uint32_t)1;
    vglyph_alignment_t align  = VGLYPH_ALIGNMENT_4;

    vglyph_surface_t* surface = vglyph_surface_create(format, width, height, align);

    vglyph_uint8_t* data = vglyph_surface_lock(surface, 0, 0, width, height);
    memset(data, 0, 28);
    vglyph_surface_unlock(surface);

    for (vglyph_uint32_t i = 0; i < 7; ++i)
    {
        vglyph_float64_t chanel = 1.0 / 6.0 * i;
        vglyph_color_t color = { chanel, chanel, 0.0, chanel };

        vglyph_surface_set_pixel(surface, i, 0, &color);
    }

    vglyph_uint8_t test_data[28] = { 
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x0A, 0x54, 0xAB,
        0x00, 0x14, 0xA9, 0x55,
        0x00, 0x21, 0x02, 0x00,
        0x00, 0x2B, 0x56, 0xAA,
        0x00, 0x35, 0xAB, 0x54,
        0x00, 0x3F, 0xFF, 0xFF };

    data = vglyph_surface_lock(surface, 0, 0, width, height);

    int result = memcmp(data, test_data, 28);

    vglyph_surface_unlock(surface);

    vglyph_object_destroy(vglyph_surface_to_object(surface));
    vglyph_object_destroy(vglyph_format_to_object(format));

    return result;
}

int test_data_render_run(void)
{
    int result = 0;

    BEGIN_TESTS()
    ADD_TEST(test_rgba_uint_data_render)
    ADD_TEST(test_rgba_uint16_data_render)
    ADD_TEST(test_rgba_uint32_data_render)
    END_TESTS(result)

    return result;
}
