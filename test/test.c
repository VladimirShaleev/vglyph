/* vglyph-test - test library for visualize glyphs
 *
 * File: test.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_glyph_info(void)
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

void show_object_state(vglyph_object_t* object)
{
    const vglyph_state_t state = vglyph_object_get_state(object);

    if (state != VGLYPH_STATE_SUCCESS)
    {
        const char* state_string = vglyph_state_to_string(state);

        printf("runtime error %d: %s\n", state, state_string);
        exit(EXIT_FAILURE);
    }
}

void show_object_type(vglyph_object_t* object)
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

void test_rgba_uint_data_render(void)
{
    printf("begin test: test_rgba_uint_data_render()\n{\n");

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
        vglyph_rgba_uint_format_create(&components, &bit_count));
    show_object_type(vglyph_format_to_object(format));

    printf("\tbits per pixel: %d\n\n", vglyph_format_get_bits_per_pixel(format));

    vglyph_uint32_t    width  = (vglyph_uint32_t)7;
    vglyph_uint32_t    height = (vglyph_uint32_t)1;
    vglyph_alignment_t align  = VGLYPH_ALIGNMENT_4;

    vglyph_surface_t* surface = vglyph_surface_create(format, width, height, align);
    show_object_type(vglyph_surface_to_object(surface));

    printf("\twidth:  %d\n", vglyph_surface_get_width(surface));
    printf("\theight: %d\n", vglyph_surface_get_height(surface));
    printf("\tpitch:  %d\n", vglyph_surface_get_pitch(surface));

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

    printf("\n\ttest data...\n");

    if (memcmp(data, test_data, 12) == 0)
        printf("\n\ttest success\n}\n\n");
    else
        printf("\n\ttest failed\n}\n\n");

    vglyph_surface_unlock(surface);

    vglyph_object_destroy(vglyph_surface_to_object(surface));
    vglyph_object_destroy(vglyph_format_to_object(format));
}

int main(void)
{
    show_glyph_info();

    test_rgba_uint_data_render();

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

    return EXIT_SUCCESS;
}
