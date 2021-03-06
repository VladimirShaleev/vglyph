﻿/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format-parser.c
 * Copyright (C) 2019 Shaleev Vladimir
 */

#include "vglyph-format-parser.h"

#define VGLYPH_FORMAT_MAX_TOKEN_SIZE 50

typedef enum _vglyph_format_token_type
{
    VGLYPH_FORMAT_TOKEN_TYPE_INVALID  = 0,
    VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL  = 1, 
    VGLYPH_FORMAT_TOKEN_TYPE_BITCOUNT = 2,
    VGLYPH_FORMAT_TOKEN_TYPE_TYPE     = 3,
} vglyph_format_token_type_t;

typedef struct _vglyph_format_token
{
    vglyph_format_token_type_t type;
    vglyph_uint_t              value;
} vglyph_format_token_t;

static const char*
_vglyph_format_parse_get_next_token(const char* format, 
                                    vglyph_format_token_t* token)
{
    if (*format == '\0')
        return NULL;

    token->type = VGLYPH_FORMAT_TOKEN_TYPE_INVALID;

    const char* start = format;
    const char symbol = *format++;
    
    if (symbol == 'r' || symbol == 'R' ||
        symbol == 'g' || symbol == 'G' ||
        symbol == 'b' || symbol == 'B' ||
        symbol == 'a' || symbol == 'A')
    {
        if (*format >= '0' && *format <= '9')
        {
            switch (symbol > 'Z' ? (symbol - 'z' + 'Z') : symbol)
            {
                case 'R':
                    token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                    token->value = VGLYPH_COMPONENT_RED;
                    break;

                case 'G':
                    token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                    token->value = VGLYPH_COMPONENT_GREEN;
                    break;

                case 'B':
                    token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                    token->value = VGLYPH_COMPONENT_BLUE;
                    break;

                case 'A':
                    token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                    token->value = VGLYPH_COMPONENT_ALPHA;
                    break;
            }
        }
    }
    else if (symbol >= '0' && symbol <= '9')
    {
        vglyph_uint_t value = symbol - '0';

        while (*format >= '0' && *format <= '9')
        {
            if (format - start > VGLYPH_FORMAT_MAX_TOKEN_SIZE)
                return format;

            value *= 10;
            value += *format++ - '0';
        }

        token->type  = VGLYPH_FORMAT_TOKEN_TYPE_BITCOUNT;
        token->value = value;
    }
    else if (symbol == '_')
    {
        while (*format != '\0')
        {
            if (format - start > VGLYPH_FORMAT_MAX_TOKEN_SIZE)
                return format;

            format++;
        }

        vglyph_uint_t length = format - ++start;

        if (length == 4)
        {
            if ((start[0] == 'u' || start[0] == 'U') &&
                (start[1] == 'i' || start[1] == 'I') &&
                (start[2] == 'n' || start[2] == 'N') &&
                (start[3] == 't' || start[3] == 'T'))
            {
                token->type  = VGLYPH_FORMAT_TOKEN_TYPE_TYPE;
                token->value = VGLYPH_FORMAT_TYPE_UINT;
            }
        }
        else if (length == 5)
        {
            if ((start[0] == 'f' || start[0] == 'F') &&
                (start[1] == 'l' || start[1] == 'L') &&
                (start[2] == 'o' || start[2] == 'O') &&
                (start[3] == 'a' || start[3] == 'A') &&
                (start[4] == 't' || start[4] == 'T'))
            {
                token->type  = VGLYPH_FORMAT_TOKEN_TYPE_TYPE;
                token->value = VGLYPH_FORMAT_TYPE_FLOAT;
            }
        }
    }

    return format;
}

void
_vglyph_format_move_component(vglyph_component_t component,
                              vglyph_rgba_components_t* components,
                              vglyph_uint8_t* channels)
{
    vglyph_uint_t index = component - VGLYPH_COMPONENT_RED;
    vglyph_uint_t next_index;

    vglyph_component_t* update_component = &components->r + index;
    vglyph_component_t* current_component;

    if (*update_component == VGLYPH_COMPONENT_ZERO)
    {
        for (vglyph_uint_t i = 0; i < index; ++i)
        {
            next_index = index - i - 1;
            current_component = &components->r + next_index;

            if (*current_component == component)
            {
                *update_component = component;
                *current_component = VGLYPH_COMPONENT_ZERO;

                channels[index] = channels[next_index];
                channels[next_index] = 0;
                break;
            }
            else if (*current_component != VGLYPH_COMPONENT_ZERO)
            {
                break;
            }
        }
    }
}

vglyph_format_type_t
_vglyph_format_parse(const char* format,
                     vglyph_rgba_components_t* components,
                     vglyph_uint8_t channels[4],
                     vglyph_uint_t* byte_count)
{
    assert(format);
    assert(components);
    assert(channels);
    assert(byte_count);

    components->r = VGLYPH_COMPONENT_ZERO;
    components->g = VGLYPH_COMPONENT_ZERO;
    components->b = VGLYPH_COMPONENT_ZERO;
    components->a = VGLYPH_COMPONENT_ZERO;

    channels[0] = 0;
    channels[1] = 0;
    channels[2] = 0;
    channels[3] = 0;

    vglyph_format_type_t type            = VGLYPH_FORMAT_TYPE_UINT;
    vglyph_component_t*  component       = &components->r;
    vglyph_uint8_t*      current_channel = channels;
    vglyph_uint_t        bits_count      = 0;

    vglyph_format_token_t token; 

    while ((format = _vglyph_format_parse_get_next_token(format, &token)) != NULL)
    {
        if (token.type == VGLYPH_FORMAT_TOKEN_TYPE_INVALID)
            return VGLYPH_FORMAT_TYPE_UNKNOWN;

        if (token.type == VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL)
        {
            *component = (vglyph_component_t)token.value;

            for (vglyph_component_t* i = &components->r; i != component; ++i)
            {
                if (*i == *component)
                    return VGLYPH_FORMAT_TYPE_UNKNOWN;
            }

            if ((format = _vglyph_format_parse_get_next_token(format, &token)) == NULL)
                return VGLYPH_FORMAT_TYPE_UNKNOWN;

            if (token.type != VGLYPH_FORMAT_TOKEN_TYPE_BITCOUNT)
                return VGLYPH_FORMAT_TYPE_UNKNOWN;

            if (token.value > UINT8_MAX)
                return VGLYPH_FORMAT_TYPE_UNKNOWN;

            ++component;
            *current_channel++ = (vglyph_uint8_t)token.value;
            bits_count += token.value;
        }
        else if (token.type == VGLYPH_FORMAT_TOKEN_TYPE_TYPE)
        {
            type = token.value;
        }
    }
    
    if (bits_count == 0)
        return VGLYPH_FORMAT_TYPE_UNKNOWN;

    _vglyph_format_move_component(VGLYPH_COMPONENT_ALPHA, components, channels);
    _vglyph_format_move_component(VGLYPH_COMPONENT_BLUE,  components, channels);
    _vglyph_format_move_component(VGLYPH_COMPONENT_GREEN, components, channels);

    *byte_count = (bits_count + 7) >> 3;
    return type;
}
