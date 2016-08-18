/*
 * The SDL Utility library
 * Copyright (c) 2016 Aggelos Kolaitis <neoaggelos@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "SDLU.h"

#include "SDL_ttf.h"
#include "SDLU_ttf_data.h"

static Uint32 font_size = SDLU_TEXT_SIZE_MEDIUM;
static TTF_Font* custom_font = NULL;

#include "SDLU_common.h"
#include <stdio.h>

/*
 * this functions uses 'goto' in order to simplify error handling
 * it shouldn't, but that way the code looks much more cleaner
 */
int
SDLU_RenderTextVa(SDL_Renderer* renderer, int x, int y, const char* format, va_list arg)
{
    int result = 0;
    TTF_Font* font = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_RWops *file = NULL;
    char* text = NULL;
    char* err = NULL;

    SDL_BlendMode blendmode;
    Uint8 r, g, b, a;

    int w, h;
    int text_w, text_h;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    /* Initialize SDL2_ttf */
    if ( TTF_Init() == -1 ) {
        SDLU_ExitError(
            SDLU_format("could not initialize SDL_ttf: %s",TTF_GetError()),
            -1
        );
    }

    /** we have a custom font **/
    if (custom_font) {
        font = custom_font;
    } else {
        /** use the builtin font **/
        file = SDL_RWFromMem( (void*) font_data, font_len );
        if (file == NULL) {
            err = "could not load TTF font";
            goto handle_error;
        }

        font = TTF_OpenFontRW( file, 0, font_size );
        if (font == NULL) {
            err = "could not open TTF font";
            goto handle_error;
        }
    }

    SDLU_vasprintf(&text, format, arg);
    if (text == NULL) {
        err = "could not generate text";
        goto handle_error;
    }

    result |= SDL_GetRendererOutputSize(renderer, &w, &h);
    result |= TTF_SizeUTF8(font, text, &text_w, &text_h);

    switch(x) {
        case SDLU_ALIGN_LEFT:     x = 0;                  break;
        case SDLU_ALIGN_CENTER:   x = (w - text_w)/2;     break;
        case SDLU_ALIGN_RIGHT:    x = w - text_w;         break;
    }

    switch(y) {
        case SDLU_ALIGN_TOP:      y = 0;                  break;
        case SDLU_ALIGN_CENTER:   y = (h - text_h) / 2;   break;
        case SDLU_ALIGN_BOTTOM:   y = h - text_h;         break;
    }

    surface = TTF_RenderUTF8_Blended( font, text, SDLU_CreateRGB(255,255,255));
    if (surface == NULL) {
        err = "could not render TTF text";
        goto handle_error;
    }

    texture = SDL_CreateTextureFromSurface( renderer, surface );
    if (texture == NULL) {
        err = "could not create texture";
        goto handle_error;
    }

    result |= SDL_GetRenderDrawColor( renderer, &r, &g, &b, &a );
    result |= SDL_GetRenderDrawBlendMode( renderer, &blendmode );

    if (blendmode != SDL_BLENDMODE_NONE) {
        result |= SDL_SetTextureAlphaMod( texture, a );
        result |= SDL_SetTextureBlendMode( texture, blendmode );
    }

    result |= SDL_SetTextureColorMod( texture, r, g, b );
    result |= SDLU_CopyTexture( renderer, texture, x, y );

    handle_error:
        /* cleanup */
        if (font && !custom_font) TTF_CloseFont(font);
        if (file) SDL_RWclose( file );
        if (surface) SDL_FreeSurface( surface );
        if (texture) SDL_DestroyTexture( texture );
        if (text) SDL_free( text );
        TTF_Quit();

    if (err)
        SDLU_ExitError( err, -1 );

    return result;
}

int
SDLU_RenderTextToSurfaceVa(SDL_Surface* surface, int x, int y, SDL_Color text_color, const char* format, va_list arg)
{
    int result = 0;
    TTF_Font* font = NULL;
    SDL_Surface* text_surf = NULL;
    SDL_RWops *file = NULL;
    SDL_Rect dstrect;
    char* text = NULL;
    char* err = NULL;

    int w, h;
    int text_w, text_h;

    if (surface == NULL)
        SDLU_ExitError("invalid parameter 'surface'", -1);

    /* Initialize SDL2_ttf */
    if ( TTF_Init() == -1 ) {
        SDLU_ExitError(
            SDLU_format("could not initialize SDL_ttf: %s",TTF_GetError()),
            -1
        );
    }

    /** we have a custom font **/
    if (custom_font) {
        font = custom_font;
    } else {
        /** use the builtin font **/
        file = SDL_RWFromMem( (void*) font_data, font_len );
        if (file == NULL) {
            err = "could not load TTF font";
            goto handle_error;
        }

        font = TTF_OpenFontRW( file, 0, font_size );
        if (font == NULL) {
            err = "could not open TTF font";
            goto handle_error;
        }
    }

    SDLU_vasprintf(&text, format, arg);
    if (text == NULL) {
        err = "could not generate text";
        goto handle_error;
    }

    w = surface->w;
    h = surface->h;

    result |= TTF_SizeUTF8(font, text, &text_w, &text_h);

    switch(x) {
        case SDLU_ALIGN_LEFT:     x = 0;                  break;
        case SDLU_ALIGN_CENTER:   x = (w - text_w)/2;     break;
        case SDLU_ALIGN_RIGHT:    x = w - text_w;         break;
    }

    switch(y) {
        case SDLU_ALIGN_TOP:      y = 0;                  break;
        case SDLU_ALIGN_CENTER:   y = (h - text_h) / 2;   break;
        case SDLU_ALIGN_BOTTOM:   y = h - text_h;         break;
    }

    text_surf = TTF_RenderUTF8_Blended(font, text, text_color);
    if (text_surf == NULL) {
        err = "could not render text";
        goto handle_error;
    }

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = text_surf->w;
    dstrect.h = text_surf->h;

    result |= SDL_BlitSurface(text_surf, NULL, surface, &dstrect);

    handle_error:

        if (font && !custom_font) TTF_CloseFont(font);
        if (file) SDL_RWclose( file );
        if (text_surf) SDL_FreeSurface( text_surf );
        if (text) SDL_free( text );
        TTF_Quit();

    if (err)
        SDLU_ExitError( err, -1 );

    return result;
}

int
SDLU_RenderText(SDL_Renderer* renderer, int x, int y, const char* format, ...)
{
    int ret;
    va_list arg;

    va_start(arg, format);
    ret = SDLU_RenderTextVa(renderer,x,y,format,arg);
    va_end(arg);

    return ret;
}

int
SDLU_RenderTextToSurface(SDL_Surface* surface, int x, int y, SDL_Color text_color, const char* format, ...)
{
    int ret;
    va_list arg;

    va_start(arg, format);
    ret = SDLU_RenderTextToSurfaceVa(surface, x, y, text_color, format, arg);
    va_end(arg);

    return ret;
}

/* uses goto for easier error handling */
void
SDLU_GetTextOutputSize(const char* text, int *w, int *h)
{
    TTF_Font* font = NULL;
    SDL_RWops* file = NULL;
    int text_w = 0, text_h = 0;
    char* err = NULL;

    if ( TTF_Init() == -1 ) {
        SDLU_ExitError(
            SDLU_format("could not initialize SDL_ttf: %s",TTF_GetError()),
        );
    }

    /** we have a custom font **/
    if (custom_font) {
        font = custom_font;
    } else {
        /** use the builtin font **/
        file = SDL_RWFromMem( (void*)font_data, font_len );
        if (file == NULL) {
            err = "could not load TTF font";
            goto handle_error;
        }

        font = TTF_OpenFontRW( file, 0, font_size );
        if (font == NULL) {
            err = "could not open TTF font";
            goto handle_error;
        }
    }

    TTF_SizeUTF8( font, text, &text_w, &text_h );

    if (w) *w = text_w;
    if (h) *h = text_h;

    handle_error:
        if (font && !custom_font) TTF_CloseFont(font);
        if (file) SDL_RWclose( file );
        TTF_Quit();

        /* this is useful only for debug builds */
        if (err)
            SDLU_ExitError(err, );
}

Uint32
SDLU_GetFontSize( )
{
    return font_size;
}

void
SDLU_SetFontSize( Uint32 size )
{
    font_size = size;
}

int
SDLU_SetTruetypeFont(void* font)
{
    /** reset font **/
    if (font == NULL) {
        SDLU_Log("resetting font");
        custom_font = NULL;
    } else {
        custom_font = (TTF_Font*)font;
    }

    return 0;
}

int
SDLU_SetTruetypeFontFile(const char* font, int size)
{
    if (font == NULL) {
        SDLU_Log("resetting font");
        custom_font = NULL;
    } else {
        if (TTF_Init() == -1) {
            custom_font = TTF_OpenFont(font, size);
        } else {
            /* the error message is set */
            return -1;
        }
        TTF_Quit();
    }
    return 0;
}

void*
SDLU_GetTruetypeFont()
{
    if (custom_font) {
        return (void*)custom_font;
    } else {
        return NULL;
    }
}
