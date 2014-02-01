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

/**
 * \file SDLU_create.h
 *
 * \brief Contains function definitions that create structures on the fly
 */

#ifndef SDLU_CREATE_H
#define SDLU_CREATE_H

#include "SDL.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Creates a new RGBA SDL_Color structure
 *
 *  \sa SDLU_CreateRGB()
 */
extern DECLSPEC SDL_Color SDLCALL SDLU_CreateRGBA(
        Uint8 r, Uint8 g, Uint8 b, Uint8 a
);

/**
 *  \brief Creates a new RGB SDL_Color structure
 *
 *  \sa SDLU_CreateRGBA()
 */
extern DECLSPEC SDL_Color SDLCALL SDLU_CreateRGB(
        Uint8 r, Uint8 g, Uint8 b
);

/**
 *  \brief Creates a new SDL_Point structure
 */
extern DECLSPEC SDL_Point SDLCALL SDLU_CreatePoint(
        int x, int y
);

/**
 *  \brief Creates a new SDL_Rect structure
 */
extern DECLSPEC SDL_Rect SDLCALL SDLU_CreateRect(
        int x, int y,
        int w, int h
);

/**
 *  \brief Creates a new SDLU_Circle structure
 */
extern DECLSPEC SDLU_Circle SDLCALL SDLU_CreateCircle(
        int x, int y,
        int r
);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_CREATE_H */

