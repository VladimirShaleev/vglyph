/* vglyph - library for visualize glyphs
 *
 * File: vglyph-format-parser.h
 * Copyright (C) 2019 Shaleev Vladimir
 */

#ifndef VGLYPH_FORMAT_PARSER_H
#define VGLYPH_FORMAT_PARSER_H

#include "vglyph-api.h"

#define VGLYPH_FORMAT_MAX_TOKEN_SYMBOLS 50

typedef enum _vglyph_format_token_type
{
    VGLYPH_FORMAT_TOKEN_TYPE_INVALID  = 0,
    VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL  = 1, 
    VGLYPH_FORMAT_TOKEN_TYPE_BITCOUNT = 2,
    VGLYPH_FORMAT_TOKEN_TYPE_TYPE     = 3,
} vglyph_format_token_type_t;

typedef enum _vglyph_format_channel_type
{
    VGLYPH_FORMAT_CHANNEL_TYPE_RED   = 0,
    VGLYPH_FORMAT_CHANNEL_TYPE_GREEN = 1,
    VGLYPH_FORMAT_CHANNEL_TYPE_BLUE  = 2,
    VGLYPH_FORMAT_CHANNEL_TYPE_ALPHA = 3,
} vglyph_format_channel_type_t;

typedef enum _vglyph_format_type
{
    VGLYPH_FORMAT_TYPE_UINT  = 0,
    VGLYPH_FORMAT_TYPE_FLOAT = 1
} vglyph_format_type_t;

typedef struct _vglyph_format_token
{
    vglyph_format_token_type_t type;
    vglyph_uint_t              value;
} vglyph_format_token_t;

static inline const char*
_vglyph_format_parse_get_next_token(const char* format, vglyph_format_token_t* token)
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
        if (*format != '\0')
        {
            if (*format >= '0' && *format <= '9')
            {
                switch (*start > 'Z' ? (*start - 'z' + 'Z') : *start)
                {
                    case 'R':
                        token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                        token->value = VGLYPH_FORMAT_CHANNEL_TYPE_RED;
                        break;

                    case 'G':
                        token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                        token->value = VGLYPH_FORMAT_CHANNEL_TYPE_GREEN;
                        break;

                    case 'B':
                        token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                        token->value = VGLYPH_FORMAT_CHANNEL_TYPE_BLUE;
                        break;

                    case 'A':
                        token->type  = VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL;
                        token->value = VGLYPH_FORMAT_CHANNEL_TYPE_ALPHA;
                        break;
                }
            }
        }
    }
    else if (symbol >= '0' && symbol <= '9')
    {
        vglyph_uint_t value = symbol - '0';

        while (*format >= '0' && *format <= '9')
        {
            if (format - start > VGLYPH_FORMAT_MAX_TOKEN_SYMBOLS)
                return NULL;

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
            if (format - start > VGLYPH_FORMAT_MAX_TOKEN_SYMBOLS)
                return NULL;

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

static inline vglyph_bool_t
_vglyph_format_parse(const char* format)
{
    vglyph_sint_t channels[4] = { -1, -1, -1, -1 };
    vglyph_format_type_t type = VGLYPH_FORMAT_TYPE_UINT;

    vglyph_format_token_t token;

    while ((format = _vglyph_format_parse_get_next_token(format, &token)) != NULL)
    {
        if (token.type == VGLYPH_FORMAT_TOKEN_TYPE_INVALID)
            return FALSE;

        if (token.type == VGLYPH_FORMAT_TOKEN_TYPE_CHANNEL)
        {
            vglyph_sint_t* channel = channels + token.value;

            if (*channel >= 0)
                return FALSE;

            if ((format = _vglyph_format_parse_get_next_token(format, &token)) == NULL)
                return FALSE;

            if (token.type != VGLYPH_FORMAT_TOKEN_TYPE_BITCOUNT)
                return FALSE;

            *channel = token.value;
        }
        else if (token.type == VGLYPH_FORMAT_TOKEN_TYPE_TYPE)
        {
            type = token.value;
        }
    }

    return TRUE;
}

#endif
