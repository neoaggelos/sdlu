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
#include "SDL.h"

/**
 *  \brief Returns the double inequality a <= b <= c
 */
#define lequal(a,b,c) \
    ( (a <= b) && (b <= c) )

/**
 *  \brief Returns the distance in pixels of two points
 *
 *  \param x1,y1 The coordinates of the 1st point
 *  \param x2,y2 The coordinates of the 2nd point
 */
#define distance(x1,y1,x2,y2) \
    SDL_sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) )

int SDLU_CollidePointCircle(SDL_Point p, SDLU_Circle c)
{
    return ( distance(p.x, p.y, c.x, c.y) <= c.r );
}

int SDLU_CollideRects(SDL_Rect a, SDL_Rect b)
{
    SDL_Rect tmp;
    int x;
    int y;
    int result;

    /*
     * if b is bigger than a, revert them otherwise the collision
     * detection might not work
     */
    tmp = a;
    if ( (a.w < b.w) && (a.h < b.h) ) {
        a = b;
        b = tmp;
    }

    /* no collision by default */
    result = 0;

    /* check if there is collision in x and y */
    x = lequal( a.x, b.x, a.x + a.w ) || lequal(a.x, b.x + b.w, a.x + a.w );
    y = lequal( a.y, b.y, a.y + a.h ) || lequal(a.y, b.y + b.h, a.y + a.h );

    if (x && y) {
        if (SDL_abs( b.y - a.y ) >= SDL_abs( b.x - a.x )) {
            result = SDLU_COLLIDE_VERTICAL;
        } else {
            result = SDLU_COLLIDE_HORIZONTAL;
        }
    }

    return result;

}

int
SDLU_CollideCircles(SDLU_Circle c1, SDLU_Circle c2)
{
    return (distance(c1.x, c1.y, c2.x, c2.y) <= c1.r + c2.r);
}

int
SDLU_CollideRectCircle(SDL_Rect r, SDLU_Circle c)
{
    int x1, y1, x2, y2;
    int cx, cy;

    x1 = r.x;
    x2 = r.x + r.w;
    y1 = r.y;
    y2 = r.y + r.h;

    cx = c.x;
    cy = c.y;

    if (
            SDLU_CollidePointCircle( SDLU_CreatePoint(x1,y1), c )
         || SDLU_CollidePointCircle( SDLU_CreatePoint(x1,y2), c )
         || SDLU_CollidePointCircle( SDLU_CreatePoint(x2,y1), c )
         || SDLU_CollidePointCircle( SDLU_CreatePoint(x2,y2), c )
       )
    {
        return 1;
    }

    if ( lequal(x1, cx, x2) ) {
        if (
                SDLU_CollidePointCircle( SDLU_CreatePoint(cx,y1), c)
             || SDLU_CollidePointCircle( SDLU_CreatePoint(cx,y2), c)
           )
        {
            return 1;
        }
    }
    else if ( lequal(y1, cy, y2) )
    {
        if (
                SDLU_CollidePointCircle( SDLU_CreatePoint(x1, cy), c )
             || SDLU_CollidePointCircle( SDLU_CreatePoint(x2, cy), c )
           )
        {
            return 1;
        }
    }

    return 0;
}

/* undefine macros */
#undef lequal
#undef distance
