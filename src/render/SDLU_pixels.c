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
#include "SDLU_common.h"
#include <stdio.h>

Uint32
SDLU_WinMapRGBA(SDL_Window* window, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 fmt;
    SDL_PixelFormat* p_fmt;

    if (window == NULL)
        SDLU_ExitError("invalid parameter 'window'", (Uint32)-1);

    fmt = SDL_GetWindowPixelFormat(window);
    p_fmt = SDL_AllocFormat( fmt );

    return SDL_MapRGBA(p_fmt,r,g,b,a);
}

Uint32
SDLU_WinMapRGB(SDL_Window* window, Uint8 r, Uint8 g, Uint8 b)
{
    return SDLU_WinMapRGBA(window,r,g,b,SDL_ALPHA_OPAQUE);
}

Uint32
SDLU_RenderMapRGBA(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_RendererInfo info;
    SDL_PixelFormat* p_fmt;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", (Uint32)-1);

    SDL_GetRendererInfo(renderer, &info);
    p_fmt = SDL_AllocFormat( info.texture_formats[0] );

    return SDL_MapRGBA( p_fmt, r, g, b, a );
}

Uint32
SDLU_RenderMapRGB(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
    return SDLU_RenderMapRGBA(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

