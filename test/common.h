/*
 * The SDL Utility library
 * Copyright (c) 2014 Aggelos Kolaitis <neoaggelos@gmail.com>
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

#ifdef UNDEF_MAIN
# undef WinMain
# undef main
#endif

/** popup an error messagebox **/
#define SDLU_Message( err ) \
    SDL_ShowSimpleMessageBox(0, "", (err), NULL)

/**
 * checks if an SDL/SDLU call is wrong.
 * if it is, it reports the error with a messagebox (if video system has been
 * initialized) or as plain output text
 *
 * this macro is used to more-readable source code, error checking
 */
#define SDL_CHECK( x ) {                                        \
    if (!(x)) {                                                 \
        SDL_Log("%s\n", SDL_GetError());                        \
        return -1;                                              \
    }                                                           \
}

#include "SDL_main.h"

/* use SDL_main when available */
#if defined(SDL_MAIN_NEEDED) || defined(SDL_MAIN_AVAILABLE)
# define SDL_MAIN_WANTED
#endif

#ifdef __cplusplus
extern "C" { extern char* GetImagePath(const char* fname); }
#else
extern char* GetImagePath(const char* fname);
#endif

#define TUX_BMP GetImagePath("tux.bmp")
#define TILE_BMP GetImagePath("tile.bmp")
#define HELP_BMP GetImagePath("help.bmp")
#define GUY_BMP GetImagePath("guy.bmp")
#define FONT_TTF GetImagePath("font.ttf")
