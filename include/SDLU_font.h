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

/**
 *  \file SDLU_font.h
 *
 *  \brief The text rendering API
 */

#ifndef SDLU_FONT_H
#define SDLU_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL.h"
#include "begin_code.h"

/*
 * SDLU_Font is basically TTF_Font, but we define it here as void.
 * that way we don't have to include SDL_ttf.h
 */
typedef void SDLU_Font;

/* same values for horizontal-vertical alignment */
enum SDLU_Alignment {
    Top = 1,            
    Left = 1,
    Center = 2,
    Mid = 2,
    Right = 3,
    Bottom = 3
};

/**
 * intializes font rendering engine, called automatically by the
 * other functions
 */
extern DECLSPEC int SDLCALL SDLU_StartFonts(void);

/**
 * load a font
 *
 * for hinting, see the TTF_HINTING_* macros from SDL_ttf.h
 * if unsure, use hinting == 1
 *
 * if freesrc is non-zero, the RWops is closed afterwards
 */
extern DECLSPEC SDLU_Font* SDLCALL SDLU_LoadFont_RW(
        SDL_RWops* src, int freesrc,
        int fontsize,
        int hinting
);

/**
 * load font from file
 */
#define SDLU_LoadFont(file, size, hint) \
    SDLU_LoadFont_RW(SDL_RWFromFile((file), "rb"), 1, (size),(hint))

/**
 * render text at 'position', aligning the text accordingly
 *
 * note that no clipping is performed if text goes out of bounds
 * (which means that position width and height can be zero without problems)
 *
 * 'font' can be an SDLU_Font* or a TTF_Font* structure
 *
 * return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_RenderUTF8Ex(
        SDL_Renderer* renderer,
        SDLU_Font *font,
        const char* string,
        SDL_Rect position,
        enum SDLU_Alignment horizontal_alignment,
        enum SDLU_Alignment vertical_alignment
);

/**
 * render text at (x, y)
 */
#define SDLU_RenderUTF8(rnd, font, str, x, y) \
    SDLU_RenderUTF8Ex((rnd), (font), (str), SDLU_CreateRect((x),(y),0,0), Top, Left) 

/**
 * get width and height of text
 */
extern DECLSPEC void SDLCALL SDLU_GetUTF8Size(SDLU_Font* font, const char* string, int *w, int *h);

/**
 * render string on a surface
 * returned surface contains the text in white color
 */
extern DECLSPEC SDL_Surface* SDLCALL SDLU_RenderUTF8Surface(SDLU_Font* font, const char* string);

/**
 * close a font
 */
extern DECLSPEC void SDLCALL SDLU_CloseFont(SDLU_Font* font);

/**
 * you should call this after finishing using the text rendering API
 */
extern DECLSPEC void SDLCALL SDLU_FinishFonts();

#include "close_code.h"

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FONT_H */
