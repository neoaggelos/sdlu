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
 *  \file SDLU_text.h
 *
 *  \brief The old, deprecated Text Rendering API
 */

/**
 *  This macro (SDLU_TYPESAFETY) is used to make the SDLU_RenderText() family of
 *  functions check their arguments similar to how printf does.
 *
 *  Unfortunately, it is GCC specific, as it uses __attribute__((format))
 */
#ifdef __GNUC__
#define SDLU_TYPESAFETY( string, check ) \
    __attribute__((format(printf, (string), (check))))
#else /** not GCC **/
#define SDLU_TYPESAFETY(a,b)
#endif

#ifndef SDLU_TEXT_H
#define SDLU_TEXT_H

#include "SDL.h"
#include "SDLU_defs.h"

#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name Text size macros
 */
/*@{*/
#define SDLU_TEXT_SIZE_SMALL 14   /**< small size  **/
#define SDLU_TEXT_SIZE_MEDIUM 20  /**< medium size **/
#define SDLU_TEXT_SIZE_LARGE 42   /**< large size  **/
/*@}*/

/**
 *  \brief Render a string of text. Uses the printf format style
 *
 *  \param renderer The renderer to draw
 *  \param x,y Coordinates of the text (can use SDLU_ALIGN macros)
 *  \param format Text to render in printf-format.
 *
 *  \note Use the SDLU_ALIGN macros to align the text.
 *
 *  \return 0 on success, -1 on error.
 *
 *  \sa SDLU_ALIGN_RIGHT
 *  \sa SDLU_ALIGN_LEFT
 *  \sa SDLU_ALIGN_CENTER
 *  \sa SDLU_ALIGN_TOP
 *  \sa SDLU_ALIGN_BOTTOM
 *  \sa SDLU_RenderTextVa()
 *  \sa SDLU_SetFontSize()
 */
extern DECLSPEC int SDLCALL SDLU_RenderText(
        SDL_Renderer* renderer,
        int x, int y,
        const char* format, ...
) SDLU_TYPESAFETY(4,5) SDL_DEPRECATED;

/**
 *  \brief Similar to SDLU_RenderText(), but pass arguments as a va_list
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_RenderText()
 *  \sa SDLU_SetFontSize()
 */
extern DECLSPEC int SDLCALL SDLU_RenderTextVa(
        SDL_Renderer* renderer,
        int x, int y,
        const char* format,
        va_list arg
) SDLU_TYPESAFETY(4,0) SDL_DEPRECATED;

/**
 *  \brief Similar to SDLU_RenderText(), but write on a surface
 *
 *  \param surface Surface to render on
 *  \param x, y Text position
 *  \param text_color Text color
 *  \param format Text to render in printf-format.
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_RenderTextToSurfaceVa()
 *  \sa SDLU_SetFontSize()
 */
extern DECLSPEC int SDLCALL SDLU_RenderTextToSurface(
        SDL_Surface* surface,
        int x, int y,
        SDL_Color text_color,
        const char* format, ...
) SDLU_TYPESAFETY(5,6) SDL_DEPRECATED;

/**
 *  \brief Similar to SDLU_RenderTextToSurface(), but pass args as a va_list
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_RenderTextToSurface()
 *  \sa SDLU_SetFontSize()
 */
extern DECLSPEC int SDLCALL SDLU_RenderTextToSurfaceVa(
        SDL_Surface* surface,
        int x, int y,
        SDL_Color text_color,
        const char* format,
        va_list arg
) SDLU_TYPESAFETY(5,0) SDL_DEPRECATED;

/**
 *  \brief Get the output size of text (in pixels)
 *
 *  \param text Text to check output size for
 *  \param w Will be filled with the output width
 *  \param h Will be filled with the output height
 */
extern DECLSPEC void SDLCALL SDLU_GetTextOutputSize(
        const char* text,
        int *w, int *h
) SDL_DEPRECATED;

/**
 *  \brief Set the font size for SDLU_RenderText()
 *
 *  \sa SDLU_RenderText()
 *  \sa SDLU_GetFontSize()
 */
extern DECLSPEC void SDLCALL SDLU_SetFontSize(Uint32 size) SDL_DEPRECATED;

/**
 *  \brief Get the current font size
 *
 *  \sa SDLU_SetFontSize()
 *  \sa SDLU_GetTextWidthHeight()
 */
extern DECLSPEC Uint32 SDLCALL SDLU_GetFontSize(void) SDL_DEPRECATED;

/**
 *  \brief Set a custom truetype font to be used by the engine
 *
 *  \param font The font to use (TTF_Font*), NULL to reset to the default font
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTruetypeFont(void* font) SDL_DEPRECATED;

/**
 *  \brief Set a custom truetype font to be used by the engine
 *
 *  \param font Path to font file to use, NULL to reset
 *  \param size Size of the font (warning: not the length of the filename)
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTruetypeFontFile(
        const char* font,
        int size
) SDL_DEPRECATED;

/**
 *  \brief Get the current truetype font
 */
extern DECLSPEC void* SDLCALL SDLU_GetTruetypeFont(void) SDL_DEPRECATED;

#ifdef __cplusplus
}
#endif

#undef SDLU_TYPESAFETY

#include "close_code.h"

#endif /* SDLU_TEXT_H */
