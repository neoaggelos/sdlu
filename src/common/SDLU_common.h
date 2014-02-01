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

#ifndef SDLU_STDLIB_H
#define SDLU_STDLIB_H

#include "SDL.h"
#include "SDLU_error.h"
#include "utlist.h"

#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDLU_malloc2( type, n )                     \
    ( type* ) SDL_malloc( (n) * sizeof(type) );

#define SDLU_malloc( type )                         \
    SDLU_malloc2( type, 1 );

#define SDLU_free( p )                              \
    SDL_free( p );

/*
 * write to s. format is the string and arg is a va_list containing the
 * arguments. memory is allocated with malloc
 *
 * returns the lenght of the string
 */
extern DECLSPEC int SDLCALL SDLU_vasprintf(
        char** s,
        const char* format,
        va_list arg
);

/**
 *  return a printf formatted string as char*
 */
extern DECLSPEC char* SDLCALL SDLU_format(const char* format, ...);

/**
 *  get the actual rect position if renderer has scale/viewport etc
 */
extern DECLSPEC SDL_Rect SDLCALL SDLU_GetScaledRect(
        SDL_Renderer* renderer,
        SDL_Rect orig,
        SDL_bool clip
);

/**
 *  save file contents in a char* buffer
 */
extern DECLSPEC char* SDLCALL SDLU_ReadFile(SDL_RWops*);

/**
 *  safe SDL_GetHint
 */
#define SDLU_GetHint(h) ( SDL_GetHint(h) ? SDL_GetHint(h) : "" )

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_STDLIB_H */
