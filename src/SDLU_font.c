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

#include "SDL.h"
#include "SDL_ttf.h"

#include "SDLU.h"
#include "SDLU_ttf_data.h"
#include "SDLU_common.h"

static int is_initialized = 0;

int
SDLU_StartFonts()
{
    if (!is_initialized) {
        int r = TTF_Init();
        is_initialized = r != -1;

        return r;
    }

    return 0;
}

SDLU_Font*
SDLU_LoadFont_RW(SDL_RWops *rw, int freerw, int size, int hinting)
{
    TTF_Font *font;
    
    SDLU_StartFonts();
    if (rw == NULL) {
        rw = SDL_RWFromMem((void*)font_data, font_len);
        if (rw == NULL)
            SDLU_ExitError("could not load default font", NULL);

        freerw = 1;
    }

    font = TTF_OpenFontRW(rw, freerw, size);

    if (font) {
        TTF_SetFontHinting(font, hinting);
        return (void*)font;
    }

    return NULL;
}

int
SDLU_RenderUTF8Ex(SDL_Renderer *renderer, void* font, const char* str,
        SDL_Rect pos, enum SDLU_Alignment hAlign, enum SDLU_Alignment vAlign)
{
    SDL_Surface *surf;
    SDL_Texture *texture;
    SDL_Rect dest;
    SDL_Color fg;

    SDLU_StartFonts();

    if (font == NULL)
        SDLU_ExitError("invalid parameter 'font'", -1);

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    /* alignment */
    TTF_SizeUTF8(font, str, &dest.w, &dest.h);

    switch(hAlign) {
        case Left: dest.x = pos.x;                          break;
        case Center: dest.x = pos.x + (pos.w - dest.w) / 2; break;
        case Right: dest.x = pos.x + pos.w - dest.w;        break;
        default: SDLU_ExitError("unknown horizontal alignment", -1);
    }

    switch(vAlign) {
        case Top: dest.y = pos.y;                           break;
        case Center: dest.y = pos.y + (pos.h - dest.h) / 2; break;
        case Bottom: dest.y = pos.y + pos.h - dest.h;       break;
        default: SDLU_ExitError("unknown vertical alignment", -1);
    }

    /* render surface */
    SDL_GetRenderDrawColor(renderer, &fg.r, &fg.g, &fg.b, &fg.a);
    surf = TTF_RenderUTF8_Blended(font, str, SDLU_CreateRGB(0xff, 0xff, 0xff));
    if (surf == NULL)
        SDLU_ExitError("could not render text on surface", -1);

    SDL_SetSurfaceColorMod(surf, fg.r, fg.g, fg.b);
    SDL_SetSurfaceAlphaMod(surf, fg.a);

    /* render on screen */
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if (texture == NULL)
        SDLU_ExitError("could not create texture", -1);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);

    return 0;
}

void
SDLU_GetUTF8Size(SDLU_Font* font, const char* string, int *w, int *h)
{
    if (font == NULL)
        SDLU_ExitError("invalid parameter 'font'", );

    SDLU_StartFonts();
    TTF_SizeUTF8(font, string, w, h);
}

SDL_Surface*
SDLU_RenderUTF8Surface(SDLU_Font* font, const char* string)
{
    if (font == NULL)
        SDLU_ExitError("invalid parameter 'font'", NULL);

    SDLU_StartFonts();

    return TTF_RenderUTF8_Blended(font, string, SDLU_CreateRGB(0xff, 0xff, 0xff));
}

void
SDLU_CloseFont(SDLU_Font *font)
{
    TTF_CloseFont(font);
}

void
SDLU_FinishFonts()
{
    if (is_initialized) {
        is_initialized = 0;
        TTF_Quit();
    }
}



