/* vglyph-test - test library for visualize glyphs
 *
 * File: test.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "vglyph.h"

#include <stdio.h>
#include <stdlib.h>

void show_glyph_info()
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

void show_object_state(void* object)
{
    const vglyph_state_t state = vglyph_object_get_state((vglyph_object_t*)object);

    if (state != VGLYPH_STATE_SUCCESS)
    {
        const char* state_string = vglyph_state_to_string(state);

        printf("runtime error %d: %s\n", state, state_string);
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    show_glyph_info();

    vglyph_point_t point1;
    point1.x = 0.5f;
    point1.y = 0.5f;
    point1.hinting = VGLYPH_HINTING_HORIZONTAL | VGLYPH_HINTING_VERTICAL;

    vglyph_point_t point2;
    point2.x = 0.3f;
    point2.y = 0.1f;
    point2.hinting = VGLYPH_HINTING_HORIZONTAL | VGLYPH_HINTING_VERTICAL;

    vglyph_figure_t* figure = vglyph_figure_create();
    show_object_state(figure);

    vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &point1);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_RELATIVE, &point2);

    vglyph_figure_destroy(figure);

    return EXIT_SUCCESS;
}
