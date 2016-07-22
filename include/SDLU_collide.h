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
 *  \file SDLU_collide.h
 *
 *  \brief Defines collision detection functions
 */

#ifndef SDLU_COLLIDE_H
#define SDLU_COLLIDE_H

#include "SDL.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \name Collision values
 *
 *  \brief These are returned by SDLU_CollideRects to indicate the type of
 *  the collision.
 */
/*@{*/
#define SDLU_COLLIDE_VERTICAL   0x01   /**< indicates a vertical collision **/
#define SDLU_COLLIDE_HORIZONTAL 0x02   /**< indicates a horizontal collision **/
/*@}*/

/**
 *  \brief Check if two given SDL_Rects collide with each other.
 *
 *  \return One of SDLU_COLLIDE_VERTICAL or SDLU_COLLIDE_HORIZONTAL in case
 *  of collision, 0 otherwise
 *
 *  \sa SDLU_COLLIDE_VERTICAL
 *  \sa SDLU_COLLIDE_HORIZONTAL
 */
extern DECLSPEC int SDLCALL SDLU_CollideRects(
        SDL_Rect a,
        SDL_Rect b
);

/**
 *  \brief Check the collision between two circles.
 *
 *  \return 1 if the two circles collide, 0 otherwise.
 */
extern DECLSPEC int SDLCALL SDLU_CollideCircles(
        SDLU_Circle c1,
        SDLU_Circle c2
);


/**
 *  \brief Check the collision between a rect and a circle.
 *
 *  \return 1 if there is collision, 0 otherwise.
 */
extern DECLSPEC int SDLCALL SDLU_CollideRectCircle(
        SDL_Rect r,
        SDLU_Circle c
);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_COLLIDE_H */
