/* vglyph-test - test library for visualize glyphs
 *
 * File: test.c
 * Copyright (C) 2016 Shaleev Vladimir
 */

#include "test-data-render.h"
#include "test-save-bitmap.h"

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

    //vglyph_format_create("G4A4", VGLYPH_ENDIANNESS_LITTLE);

    //vglyph_point_t point1;
    //point1.x = 0.1f;
    //point1.y = 0.9f;
    //
    //vglyph_point_t point2;
    //point2.x = 0.7f;
    //point2.y = -0.7f;
    //
    //vglyph_point_t point3;
    //point3.x = 0.1f;
    //point3.y = 0.1f;
    //
    //vglyph_point_t point4;
    //point4.x = -0.5f;
    //point4.y = 0.3f;
    //
    //vglyph_point_t point5;
    //point5.x = -0.1f;
    //point5.y = 0.5f;
    //
    //vglyph_point_t point6;
    //point6.x = 0.05f;
    //point6.y = 0.3f;
    //
    //vglyph_point_t point7;
    //point7.x = 0.1f;
    //point7.y = -0.1f;
    //
    //vglyph_point_t p0 = { 0.1f, 0.80f };
    //vglyph_point_t p1 = { 0.25f, -0.099f };
    //vglyph_point_t r  = { 0.12f, 0.055f };

    vglyph_figure_t* figure = vglyph_figure_create();
    show_object_type(vglyph_figure_to_object(figure));

    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &point1);
    //vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_RELATIVE, &point2);
    //vglyph_figure_draw_curveto_cubic(figure, VGLYPH_COORDINATE_RELATIVE, &point5, &point3, &point4);
    //vglyph_figure_draw_lineto_horizontal(figure, VGLYPH_COORDINATE_RELATIVE, 0.1f);
    //vglyph_figure_draw_lineto_vertical(figure, VGLYPH_COORDINATE_RELATIVE, 0.1f);
    //vglyph_figure_draw_closepath(figure);
    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &point6);
    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_RELATIVE, &point3);
    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_RELATIVE, &point7);
    //vglyph_figure_draw_closepath(figure);
    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p0);
    //vglyph_figure_draw_arc(figure, VGLYPH_COORDINATE_RELATIVE, &p1, &r, -15.0f, 1, 0);
    //vglyph_figure_draw_arc(figure, VGLYPH_COORDINATE_ABSOLUTE, &p0, &r, -15.0f, 1, 0);
    //vglyph_figure_draw_closepath(figure);

    vglyph_point_t p0  = {  0.5813305592383244f,      1.0f - 0.8566155047802226f       };
    vglyph_point_t p1  = {  0.5559548825974758f,      1.0f - 0.7366581420548357f       };
    vglyph_point_t p2  = {  0.5498032417531107f,      1.0f - 0.7366581420548357f       };
    vglyph_point_t p3  = {  0.4236942381833586f,      1.0f - 0.8443122230914923f       };
    vglyph_point_t p4  = {  0.4867487066718468f,      1.0f - 0.8158608592140126f       };
    vglyph_point_t p5  = {  0.26759591058045373f,     1.0f - 0.8719946401875234f       };
    vglyph_point_t p6  = {  0.36140868317993124f,     1.0f - 0.8719946401875234f       };
    vglyph_point_t p7  = {  0.07074287914266009f,     1.0f - 0.8074023114325257f       };
    vglyph_point_t p8  = {  0.14225590373673214f,     1.0f - 0.8719946401875234f       };
    vglyph_point_t p9  = { -0.000001171936473524384f, 1.0f - 0.6236213669552626f       };
    vglyph_point_t p10 = { -0.000001171936473524384f, 1.0f - 0.7428097828992009f       };
    vglyph_point_t p11 = {  0.40831506947967f,        1.0f - 0.3560243242976213f       };
    vglyph_point_t p12 = { -0.000001171936473524384f, 1.0f - 0.3683276059863516f       };
    vglyph_point_t p13 = {  0.551341135316008f,       1.0f - 0.3514106103125414f       };
    vglyph_point_t p14 = {  0.551341135316008f,       1.0f - 0.29912152994988617f      };
    vglyph_point_t p15 = {  0.5082794829235127f,      1.0f - 0.15301964369136556f      };
    vglyph_point_t p16 = {  0.551341135316008f,       1.0f - 0.19992604663929825f      };
    vglyph_point_t p17 = {  0.3721740713057642f,      1.0f - 0.10534431061017813f      };
    vglyph_point_t p18 = {  0.4659868439052417f,      1.0f - 0.10534431061017813f      };
    vglyph_point_t p19 = {  0.13379739757573006f,     1.0f - 0.16993668930975758f      };
    vglyph_point_t p20 = {  0.2668269471508111f,      1.0f - 0.10534431061017813f      };
    vglyph_point_t p21 = {  0.0945805456832538f,      1.0f - 0.07227914950664882f      };
    vglyph_point_t p22 = {  0.23068598227329318f,     1.0f - 0.01922111403844795f      };
    vglyph_point_t p23 = {  0.15686607571439026f,     1.0f - 0.03844502913552539f      };
    vglyph_point_t p24 = {  0.3798636723058024f,      1.0f + 0.0000028233016083215393f };
    vglyph_point_t p25 = {  0.30527483561364477f,     1.0f + 0.0000028233016083215393f };
    vglyph_point_t p26 = {  0.6028612688972146f,      1.0f - 0.0668964429575869f       };
    vglyph_point_t p27 = {  0.5305793058457908f,      1.0f + 0.0000028233016083215393f };
    vglyph_point_t p28 = {  0.6759122120264749f,      1.0f - 0.28143548760546366f      };
    vglyph_point_t p29 = {  0.6759122120264749f,      1.0f - 0.13379571610814267f      };
    vglyph_point_t p30 = {  0.6759122120264749f,      1.0f - 0.8566155047802226f       };
    vglyph_point_t p31 = {  0.5813305592383244f,      1.0f - 0.8566155047802226f       };
    vglyph_point_t p32 = {  0.2929715206285266f,      1.0f - 0.7666474660879885f       };
    vglyph_point_t p33 = {  0.4798281523424208f,      1.0f - 0.7012861239587664f       };
    vglyph_point_t p34 = {  0.412159903276077f,       1.0f - 0.7666474660879885f       };
    vglyph_point_t p35 = {  0.5482653148938255f,      1.0f - 0.5182742927448913f       };
    vglyph_point_t p36 = {  0.5482653148938255f,      1.0f - 0.6359246486439929f       };
    vglyph_point_t p37 = {  0.5482653148938255f,      1.0f - 0.44214752919344846f      };
    vglyph_point_t p38 = {  0.42061841776117603f,     1.0f - 0.44753028984914067f      };
    vglyph_point_t p39 = {  0.20069665824014038f,     1.0f - 0.49520558963394024f      };
    vglyph_point_t p40 = {  0.2683648573619024f,      1.0f - 0.45291298391205714f      };
    vglyph_point_t p41 = {  0.13379739757573006f,     1.0f - 0.6251593271109357f       };
    vglyph_point_t p42 = {  0.13379739757573006f,     1.0f - 0.5367293151671504f       };
    vglyph_point_t p43 = {  0.17532106484026144f,     1.0f - 0.7305065012104706f       };
    vglyph_point_t p44 = {  0.13379739757573006f,     1.0f - 0.6943654697401769f       };
    vglyph_point_t p45 = {  0.2929715206285266f,      1.0f - 0.7666474660879885f       };
    vglyph_point_t p46 = {  0.21761368721033847f,     1.0f - 0.7666474660879885f       };
     
    vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p0);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p1);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p2);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p3, &p4);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p5, &p6);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p7, &p8);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p9, &p10);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p11, &p12);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p13);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p14);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p15, &p16);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p17, &p18);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p19, &p20);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p21);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p22, &p23);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p24, &p25);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p26, &p27);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p28, &p29);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p30);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p31);
    vglyph_figure_draw_closepath(figure);
    vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p32);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p33, &p34);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p35, &p36);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p37);
    vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &p38);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p39, &p40);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p41, &p42);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p43, &p44);
    vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_ABSOLUTE, &p45, &p46);
    vglyph_figure_draw_closepath(figure);

    //vglyph_point_t lb = { 0.0f, 0.0f };
    //vglyph_point_t lr = { 1.0f, 0.0f };
    //vglyph_point_t rt = { 1.0f, 1.0f };
    //vglyph_point_t tl = { 0.0f, 1.0f };
    //
    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &lb);
    //vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &lr);
    //vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &rt);
    //vglyph_figure_draw_lineto(figure, VGLYPH_COORDINATE_ABSOLUTE, &tl);
    //vglyph_figure_draw_closepath(figure);

    //vglyph_point_t b0 = { 0.4f, 0.4f };
    //vglyph_point_t b1 = { 0.2f, 0.3f };
    //vglyph_point_t b2 = { 0.3f, -0.1f };
    //vglyph_point_t b3 = { -0.4f, 0.1f };
    //vglyph_point_t b4 = { 0.4f, -0.1f };
    //
    //vglyph_figure_draw_moveto(figure, VGLYPH_COORDINATE_ABSOLUTE, &b0);
    //vglyph_figure_draw_curveto_quadratic(figure, VGLYPH_COORDINATE_RELATIVE, &b1, &b2);
    //vglyph_figure_draw_curveto_quadratic_smooth(figure, VGLYPH_COORDINATE_RELATIVE, &b3);
    //vglyph_figure_draw_curveto_cubic_smooth(figure, VGLYPH_COORDINATE_ABSOLUTE, &b0, &b0);
    //vglyph_figure_draw_closepath(figure);

    vglyph_glyph_t* glyph = vglyph_glyph_create(figure);
    vglyph_object_destroy(vglyph_figure_to_object(figure));
    show_object_type(vglyph_glyph_to_object(glyph));

    vglyph_glyph_set_horizontal_advance(glyph, 0.8f);
    vglyph_glyph_set_horizontal_bearing_x(glyph, 0.0f);
    vglyph_glyph_set_horizontal_bearing_y(glyph, p5.y);

    vglyph_packaging_bytes_t packaging_bytes;
    packaging_bytes.byte_count = 4;
    packaging_bytes.endianness = VGLYPH_ENDIANNESS_LITTLE;

    vglyph_rgba_components_t components;
    components.r = VGLYPH_COMPONENT_ZERO;
    components.g = VGLYPH_COMPONENT_RED;
    components.b = VGLYPH_COMPONENT_GREEN;
    components.a = VGLYPH_COMPONENT_BLUE;

    vglyph_rgba_uint_bit_count_t bit_count;
    bit_count.r = 8;
    bit_count.g = 8;
    bit_count.b = 8;
    bit_count.a = 8;

    vglyph_format_t* format = vglyph_rgba_uint_format_to_format(
        vglyph_rgba_uint_format_create(&packaging_bytes, &components, &bit_count));

    char path[512] = { '\0' };
    strcpy(path, app_dir);
    strcat(path, "glyph.bmp");

    //point3.y /= 2;
    //
    //vglyph_float32_t w = vglyph_glyph_get_width(glyph);
    //vglyph_float32_t h = vglyph_glyph_get_height(glyph);
    //
    vglyph_point_t scale = { 2.0f, 2.0f };
    //vglyph_point_t viewport = { 200.0f, 200.0f };

    vglyph_surface_t* surface = vglyph_surface_create(format, 800, 200, VGLYPH_ALIGNMENT_4);
    vglyph_color_t fill_color;
    fill_color.red   = 1.0;
    fill_color.green = 1.0;
    fill_color.blue  = 1.0;
    fill_color.alpha = 1.0;
    vglyph_color_t glyph_color;
    glyph_color.red   = 0.0;
    glyph_color.green = 0.0;
    glyph_color.blue  = 0.0;
    glyph_color.alpha = 1.0;
    vglyph_surface_set_multisampling(surface, VGLYPH_MULTISAMPLING_16);
    vglyph_surface_fill(surface, 0, 0, 800, 200, &fill_color);

    //// for (int i = 0; i < 9; ++i)
    //// {
    ////     vglyph_point_t pos = { i * 80.0f, 150.0f };
    ////     vglyph_surface_draw_glyph(surface, glyph, i * 5.0f, &glyph_color, &pos, 0, 0, 0.0f);
    //// }
    //// 
    //// for (int i = 0; i < 9; ++i)
    //// {
    ////     vglyph_point_t pos = { i * 80.0f + 70.0f, 20.0f };
    ////     vglyph_point_t origin = { 10.0f, 10.0f };
    ////     vglyph_surface_draw_glyph(surface, glyph, 24.0f, &glyph_color, &pos, &origin, 0, i * 40.0f);
    //// }
    //// 
    //// vglyph_point_t pos1 = { 350.0f, 50.0f };
    //// vglyph_surface_draw_glyph(surface, glyph, 70.0f, &glyph_color, &pos1, 0, 0, 0.0f);
    //// 
    //// vglyph_point_t pos2 = { 30.0f, 50.0f };
    //// vglyph_point_t pos3 = { 40.0f, 50.0f };
    //// vglyph_color_t red = { 1.0, 0.5, 0.0, 0.5 };
    //// vglyph_color_t green = { 0.5, 1.0, 0.0, 0.5 };
    //// vglyph_surface_draw_glyph(surface, glyph, 70.0f, &red, &pos2, 0, 0, 0.0f);
    //// vglyph_surface_draw_glyph(surface, glyph, 70.0f, &green, &pos3, 0, 0, 0.0f);
    //// 
    //// vglyph_point_t pos4 = { 700.0f, 50.0f };
    //// vglyph_surface_set_multisampling(surface, VGLYPH_MULTISAMPLING_1);
    //// vglyph_surface_draw_glyph(surface, glyph, 70.0f, &glyph_color, &pos4, 0, 0, 0.0f);

    //vglyph_surface_draw_glyph(surface, glyph, 120.0f, &glyph_color, 0, 0, 0, 0.0f);
    //vglyph_surface_draw_glyph(surface, glyph, 200.0f, &glyph_color, &pos3, 0, 0, 0.0f);
    vglyph_point_t pos0 = { 10.0f, 10.0f };
    vglyph_point_t pos1 = { 10.0f, 50.0f };
    vglyph_point_t pos2 = { 100.0f, 0.0f };
    vglyph_point_t pos3 = { 100.0f, 100.0f };
    vglyph_point_t viewport = { 100.0f, 100.0f };
    vglyph_point_t s = { 1.5f, 0.5f };

    vglyph_color_t glyph_color_green = { 0.0f, 1.0f, 0.0f, 1.0f };
    vglyph_color_t glyph_color_blue = { 0.0f, 1.0f, 1.0f, 1.0f };
    vglyph_color_t glyph_color_red = { 1.0f, 0.0f, 0.0f, 1.0f };

    //vglyph_surface_draw_glyph_viewport(surface, glyph, &glyph_color, &pos0, &viewport, 0, 0.0f, 1);
    //vglyph_surface_draw_glyph_viewport(surface, glyph, &glyph_color_green, &pos1, &viewport, 0, 0.0f, 1);
    //vglyph_surface_draw_glyph_viewport(surface, glyph, &glyph_color_blue, &pos2, &viewport, 0, 0.0f, 1);
    //vglyph_surface_draw_glyph_viewport(surface, glyph, &glyph_color_red, &pos3, &viewport, 0, 0.0f, 1);

    vglyph_face_t* face = vglyph_face_create();
    show_object_type(vglyph_face_to_object(face));
    vglyph_face_add_glyph(face, glyph, 'a');

    vglyph_surface_draw_text(surface, face, 14, "aaaaa", &glyph_color, &pos0, 0, &s, 40, 0);
    vglyph_surface_draw_text(surface, face, 30, "aaaaa", &glyph_color, &pos1, 0, &s, 40, 0);

    vglyph_object_destroy(vglyph_face_to_object(face));

    bitmap_save(surface, path);

    vglyph_object_destroy(vglyph_surface_to_object(surface));
    vglyph_object_destroy(vglyph_format_to_object(format));
    vglyph_object_destroy(vglyph_glyph_to_object(glyph));

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
