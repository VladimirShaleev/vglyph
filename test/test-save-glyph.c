/* vglyph-test - test library for visualize glyphs
 *
 * File: test-save-glyph.c
 * Copyright (C) 2019 Shaleev Vladimir
 */

#include "test-save-bitmap.h"

static char app_dir[512] = { '\0' };

static vglyph_glyph_t* create_glyph(void)
{
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

    vglyph_figure_t* figure = vglyph_figure_create();
    
    if (vglyph_object_get_state(vglyph_figure_to_object(figure)) != VGLYPH_STATE_SUCCESS)
    {
        vglyph_object_destroy(vglyph_figure_to_object(figure));
        return NULL;
    }

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

    vglyph_glyph_t* glyph = vglyph_glyph_create(figure);
    vglyph_object_destroy(vglyph_figure_to_object(figure));

    if (vglyph_object_get_state(vglyph_glyph_to_object(glyph)) != VGLYPH_STATE_SUCCESS)
    {
        vglyph_object_destroy(vglyph_glyph_to_object(glyph));
        return NULL;
    }

    vglyph_glyph_set_horizontal_advance(glyph, 0.8f);
    vglyph_glyph_set_horizontal_bearing_x(glyph, 0.0f);
    vglyph_glyph_set_horizontal_bearing_y(glyph, p5.y);

    return glyph;
}

static int test_save_glyph(void)
{
    vglyph_glyph_t* glyph = create_glyph();

    if (!glyph)
        return 1;

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

    if (vglyph_object_get_state(vglyph_format_to_object(format)) != VGLYPH_STATE_SUCCESS)
    {
        vglyph_object_destroy(vglyph_format_to_object(format));
        return 1;
    }

    vglyph_surface_t* surface = vglyph_surface_create(format, 800, 200, VGLYPH_ALIGNMENT_4);
    vglyph_object_destroy(vglyph_format_to_object(format));

    if (vglyph_object_get_state(vglyph_surface_to_object(surface)) != VGLYPH_STATE_SUCCESS)
    {
        vglyph_object_destroy(vglyph_surface_to_object(surface));
        return 1;
    }

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

    vglyph_color_t red_color;
    red_color.red   = 1.0;
    red_color.green = 0.5;
    red_color.blue  = 0.0;
    red_color.alpha = 0.5;
    
    vglyph_color_t green_color;
    green_color.red   = 0.5;
    green_color.green = 1.0;
    green_color.blue  = 0.0;
    green_color.alpha = 0.5;

    vglyph_surface_set_multisampling(surface, VGLYPH_MULTISAMPLING_16);
    vglyph_surface_fill(surface, 0, 0, 800, 200, &fill_color);

    for (int i = 0; i < 9; ++i)
    {
        vglyph_point_t pos = { i * 80.0f, 150.0f };
        vglyph_surface_draw_glyph(surface, glyph, i * 5.0f, &glyph_color, &pos, 0, 0, 0.0f, 0);
    }
    
    for (int i = 0; i < 9; ++i)
    {
        vglyph_point_t pos    = { i * 80.0f + 70.0f, 20.0f };
        vglyph_point_t origin = { 10.0f, 10.0f };
        vglyph_surface_draw_glyph(surface, glyph, 24.0f, &glyph_color, &pos, &origin, 0, i * 40.0f, 0);
    }
    
    vglyph_point_t pos1 = { 350.0f, 50.0f };
    vglyph_point_t pos2 = { 30.0f,  50.0f };
    vglyph_point_t pos3 = { 40.0f,  50.0f };
    vglyph_point_t pos4 = { 700.0f, 50.0f };

    vglyph_surface_draw_glyph(surface, glyph, 70.0f, &glyph_color, &pos1, 0, 0, 0.0f, 0);
    vglyph_surface_draw_glyph(surface, glyph, 70.0f, &red_color,   &pos2, 0, 0, 0.0f, 0);
    vglyph_surface_draw_glyph(surface, glyph, 70.0f, &green_color, &pos3, 0, 0, 0.0f, 0);
    
    vglyph_surface_set_multisampling(surface, VGLYPH_MULTISAMPLING_1);
    vglyph_surface_draw_glyph(surface, glyph, 70.0f, &glyph_color, &pos4, 0, 0, 0.0f, 0);

    char path[512] = { '\0' };
    strcpy(path, app_dir);
    strcat(path, "glyph.bmp");

    int result = bitmap_save(surface, path) == 0;

    vglyph_object_destroy(vglyph_surface_to_object(surface));
    vglyph_object_destroy(vglyph_glyph_to_object(glyph));

    return result;
}

int test_save_glyph_run(const char* dir)
{
    strcpy(app_dir, dir);
    int result = 0;
    
    BEGIN_TESTS()
    ADD_TEST(test_save_glyph)
    END_TESTS(result)

    return result;
}
