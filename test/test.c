/* vglyph-test - test library for visualize glyphs
 *
 * File: test.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "test-data-render.h"
#include "test-save-bitmap.h"
#include "test-save-glyph.h"

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
        else if (vglyph_object_is_cast(object, vglyph_get_transform_type()))
            printf("object type: vglyph_transform_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_rgba_uint_format_type()))
            printf("object type: vglyph_rgba_uint_format_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_format_type()))
            printf("object type: vglyph_format_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_face_type()))
            printf("object type: vglyph_face_t\n");
        else if (vglyph_object_is_cast(object, vglyph_get_glyph_type()))
            printf("object type: vglyph_glyph_t\n");
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

int main(int argc, char* argv[])
{
    show_glyph_info();

    char* app_name = argv[0];
    char* last = strrchr(app_name, '\\');

    char app_dir[512] = { '\0' };
    strncpy(app_dir, app_name, last - app_name + 1);

    int result = 0;
    result |= test_data_render_run();
    result |= test_save_bitmap_run(app_dir);
    result |= test_save_glyph_run(app_dir);

    //vglyph_format_create("G4A4", VGLYPH_ENDIANNESS_LITTLE);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
