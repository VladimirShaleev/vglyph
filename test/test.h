/* vglyph-test - test library for visualize glyphs
 *
 * File: test.h
 * Copyright (C) 2019 Shaleev Vladimir
 */

#include "vglyph.h"
#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void show_object_state(vglyph_object_t* object);

void show_object_type(vglyph_object_t* object);
