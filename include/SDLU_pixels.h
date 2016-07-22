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
 *  \file SDLU_pixels.h
 *
 *  \brief Defines pixel and pixel values manipulation functions
 */


#ifndef SDLU_PIXELS_H
#define SDLU_PIXELS_H

#include "SDL.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Calculate a pixel value of the specified color for the given window.
 *
 *  \return The calculated pixel value, (Uint32)-1 on error
 *
 *  \sa SDLU_WinMapRGBA()
 */
extern DECLSPEC Uint32 SDLCALL SDLU_WinMapRGB(
        SDL_Window* window,
        Uint8 r, Uint8 g, Uint8 b
);

/**
 *  \brief Calculate a pixel value of the specified color for the given window.
 *
 *  \return The calculated pixel value, (Uint32)-1 on error
 *
 *  \sa SDLU_WinMapRGB()
 */
extern DECLSPEC Uint32 SDLCALL SDLU_WinMapRGBA(
        SDL_Window* window,
        Uint8 r, Uint8 g, Uint8 b, Uint8 a
);

/**
 *  \brief Calculate a pixel value of the specified color for the given renderer
 *
 *  \return The calculated pixel value, (Uint32)-1 on error
 *
 *  \sa SDLU_RenderMapRGB()
 */
extern DECLSPEC Uint32 SDLCALL SDLU_RenderMapRGBA(
        SDL_Renderer* renderer,
        Uint8 r, Uint8 g, Uint8 b, Uint8 a
);

/**
 *  \brief Retuens a pixel value of the specified color for the given renderer.
 *
 *  \return The calculated pixel value, (Uint32)-1 on error
 *
 *  \sa SDLU_RenderMapRGBA()
 */
extern DECLSPEC Uint32 SDLCALL SDLU_RenderMapRGB(
        SDL_Renderer* renderer,
        Uint8 r, Uint8 g, Uint8 b
);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_PIXELS_H */
