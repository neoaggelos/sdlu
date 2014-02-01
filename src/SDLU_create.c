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

#include "SDLU.h"
#include "SDLU_create.h"

SDL_Color
SDLU_CreateRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

SDL_Color
SDLU_CreateRGB(Uint8 r, Uint8 g, Uint8 b)
{
    return SDLU_CreateRGBA( r, g, b, SDL_ALPHA_OPAQUE);
}

SDL_Point
SDLU_CreatePoint(int x, int y)
{
    SDL_Point p;
    p.x = x;
    p.y = y;
    return p;
}

SDLU_Circle
SDLU_CreateCircle(int x, int y, int r)
{
    SDLU_Circle c;
    c.x = x;
    c.y = y;
    c.r = r;
    return c;
}

SDL_Rect
SDLU_CreateRect(int x, int y, int w, int h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}




