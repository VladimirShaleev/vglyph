/* vglyph-test - test library for visualize glyphs
 *
 * File: test.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph.h"
#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char app_dir[512] = { '\0' };

static void show_glyph_info(void)
{
#ifdef VGLYPH_STATIC_BUILD
    printf("=================================================\n");
    printf("test vglyph-static - library for visualize glyphs\n");
    printf("=================================================\n\n");
#else
    printf("==========================================\n");
    printf("test vglyph - library for visualize glyphs\n");
    printf("==========================================\n\n");
#endif

    printf("compile vglyph version: %s (%d)\n", VGLYPH_VERSION_STRING, VGLYPH_VERSION);
    printf("runtime vglyph version: %s (%d)\n\n", vglyph_version_string(), vglyph_version());

    if (!vglyph_is_version_compatible(VGLYPH_VERSION))
    {
        printf("compile and runtime versions not compatible\n");
        exit(EXIT_FAILURE);
    }
}

static void show_object_state(vglyph_object_t* object)
{
    const vglyph_state_t state = vglyph_object_get_state(object);

    if (state != VGLYPH_STATE_SUCCESS)
    {
        const char* state_string = vglyph_state_to_string(state);

        printf("runtime error %d: %s\n", state, state_string);
        exit(EXIT_FAILURE);
    }
}

static void show_object_type(vglyph_object_t* object)
{
    const vglyph_state_t state = vglyph_object_get_state(object);

    if (state == VGLYPH_STATE_SUCCESS)
    {
        if (vglyph_object_is_cast(object, vglyph_get_surface_type()))
            printf("object type: vglyph_surface_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_rgba_uint_format_type()))
            printf("object type: vglyph_rgba_uint_format_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_format_type()))
            printf("object type: vglyph_format_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_figure_type()))
            printf("object type: vglyph_figure_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_type_type()))
            printf("object type: vglyph_type_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_object_type()))
            printf("object type: vglyph_object_t\n");
    }
    else
    {
        show_object_state(object);
    }
}

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

    for (vglyph_sint32_t i = 0; i < 7; ++i)
    {
        vglyph_float64_t chanel = 1.0 / 6.0 * i;
        vglyph_color_t color = { chanel, chanel, chanel, chanel };

        vglyph_surface_set_pixel(surface, (vglyph_float32_t)i, 0.0f, &color);
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

    for (vglyph_sint32_t i = 0; i < 3; ++i)
    {
        vglyph_float64_t chanel = 1.0 / 2.0 * i;
        vglyph_color_t color = { chanel, chanel, chanel, chanel };

        vglyph_surface_set_pixel(surface, (vglyph_float32_t)i, 0.0f, &color);
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

    for (vglyph_sint32_t i = 0; i < 7; ++i)
    {
        vglyph_float64_t chanel = 1.0 / 6.0 * i;
        vglyph_color_t color = { chanel, chanel, 0.0, chanel };

        vglyph_surface_set_pixel(surface, (vglyph_float32_t)i, 0.0f, &color);
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
            vglyph_surface_set_pixel(surface, (vglyph_float32_t)x, (vglyph_float32_t)y, &color);
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

#define BEGIN_TESTS()                                                      \
{                                                                          \
    struct                                                                 \
    {                                                                      \
        int (*func)(void);                                                 \
        char* name;                                                        \
    } tests[] = { 
#define ADD_TEST(func)                                                     \
        { func, #func },
#define END_TESTS(result)                                                  \
    };                                                                     \
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i)             \
    {                                                                      \
        int failed = tests[i].func() != 0;                                 \
        result |= failed;                                                  \
        printf("%s : %s\n", tests[i].name, failed ? "FAILED" : "SUCCESS"); \
    }                                                                      \
}

int main(int argc, char* argv[])
{
    show_glyph_info();

    char* app_name = argv[0];
    char* last = strrchr(app_name, '\\');
    strncpy(app_dir, app_name, last - app_name + 1);

    int result = 0;

    BEGIN_TESTS()
    ADD_TEST(test_rgba_uint_data_render)
    ADD_TEST(test_rgba_uint16_data_render)
    ADD_TEST(test_rgba_uint32_data_render)
    END_TESTS(result)
        
    BEGIN_TESTS()
    ADD_TEST(test_save_bitmap_x1r5g5b5)
    ADD_TEST(test_save_bitmap_x4r4g4b4)
    ADD_TEST(test_save_bitmap_r5g6b5)
    ADD_TEST(test_save_bitmap_r8g8b8)
    END_TESTS(result)

    return result;

    //vglyph_point_t point1;
    //point1.x = 0.5f;
    //point1.y = 0.5f;
    //point1.hinting = VGLYPH_HINTING_ALL;

    //vglyph_point_t point2;
    //point2.x = 0.3f;
    //point2.y = 0.1f;
    //point2.hinting = VGLYPH_HINTING_ALL;

    //vglyph_figure_t* figure = vglyph_figure_create();
    //show_object_type(vglyph_figure_to_object(figure));

    //vglyph_type_t* type = vglyph_object_get_type(vglyph_figure_to_object(figure));
    //show_object_type(vglyph_type_to_object(type));

    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &point1);
    //vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_RELATIVE, &point2);

    //vglyph_object_destroy(vglyph_type_to_object(type));
    //vglyph_object_destroy(vglyph_figure_to_object(figure));

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
