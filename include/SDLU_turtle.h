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
 *  \file SDLU_turtle.h
 *
 *  \brief The turtle drawing API
 */

#ifndef SDLU_TURTLE_H
#define SDLU_TURTLE_H

#include "SDL.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief The 'turtle' structure
 */
struct SDLU_Turtle {
    Uint32 id;                  /**< unique identifier                  **/
    const char* name;           /**< user-defined 'name' of the turtle  **/

    int x, y;                   /**< current position on screen         **/
    int direction;              /**< current direction (angle)          **/
    SDL_Renderer *renderer;     /**< renderer to draw                   **/

    Uint8 r, g, b, a;           /**< current drawing color              **/
    SDL_BlendMode blendmode;    /**< current blendmode                  **/
    SDL_bool drawing;           /**< whether to draw or not             **/

    struct SDLU_Turtle *next;   /**< DO NOT TOUCH                       **/
};
typedef struct SDLU_Turtle SDLU_Turtle;

/**
 *  \brief Create a new turtle
 */
extern DECLSPEC SDLU_Turtle* SDLCALL SDLU_CreateTurtle(SDL_Renderer* renderer);

/**
 *  \brief Set the drawing color (RGBA) of a turtle
 *
 *  \param turtle Turtle to change
 *  \param r, g, b, a Red, green, blue and alpha of the new color
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTurtleDrawColor(
        SDLU_Turtle* turtle,
        Uint8 r, Uint8 g, Uint8 b, Uint8 a
);

/**
 *  \brief Set the drawing blendmode of a turtle
 *
 *  \param turtle Turtle to change
 *  \param blendmode The new SDL_BlendMode of the turtle
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTurtleDrawBlendMode(
        SDLU_Turtle* turtle,
        SDL_BlendMode blendmode
);

/**
 *  \brief Set whether the turtle draws as it 'moves'
 *
 *  \param turtle Turtle to change
 *  \param draw 0 to disable drawing, any other value to enable it
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTurtleDraw(
        SDLU_Turtle* turtle,
        int draw
);

/**
 *  \brief Move the turtle
 *
 *  \param turtle Turtle to move
 *  \param steps Number of steps to move (1 step = 1 pixel if scale = 1)
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_MoveTurtle(
        SDLU_Turtle* turtle,
        int steps
);

/**
 *  \brief Rotate a turtle (positive means to the right, negative to the left)
 *
 *  \param turtle Turtle to rotate
 *  \param angle Angle (in degrees)
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_RotateTurtle(
        SDLU_Turtle* turtle,
        int angle
);

/**
 *  \name Direction macros for the turtle
 */
/*@{*/
#define SDLU_TURTLE_RIGHT 0
#define SDLU_TURTLE_DOWN 90
#define SDLU_TURTLE_LEFT 180
#define SDLU_TURTLE_UP 270
/*@}*/

/**
 *  \brief Set the direction of a turtle
 *
 *  \param turtle The turtle
 *  \param angle Angle (in degrees) -- 0 means vertical face-down
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTurtleDirection(
        SDLU_Turtle* turtle,
        int angle
);

/**
 *  \brief Set the position of a turtle
 *
 *  \param turtle The turtle
 *  \param x, y The new position
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetTurtlePosition(
        SDLU_Turtle* turtle,
        int x, int y
);

/**
 *  \brief Move turtle in the middle of the screen, face up, ready to draw
 *
 *  \param turtle Turtle to reset
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_ResetTurtle(SDLU_Turtle* turtle);

/**
 *  \brief Destroy a turtle
 */
extern DECLSPEC int SDLCALL SDLU_DestroyTurtle(SDLU_Turtle* turtle);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_TURTLE_H */
