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
#include "SDLU_common.h"

/* PI */
#define SDLU_PI 3.14159265358979323846

static Uint32 next_id = 1;
static SDLU_Turtle* turtles = NULL;

static int
SDLU_round(double in)
{
    int out = (int)in;
    if (in - (int)in >= 0.5) {
        ++out;
    }
    return out;
}

SDLU_Turtle*
SDLU_CreateTurtle(SDL_Renderer *renderer)
{
    SDLU_Turtle* turtle;
    int renderer_w, renderer_h;

    turtle = SDLU_malloc(SDLU_Turtle);
    if (turtle == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    turtle->id = next_id++;
    turtle->name = NULL;
    turtle->renderer = renderer;

    SDL_GetRendererOutputSize(renderer, &renderer_w, &renderer_h);
    turtle->x = renderer_w / 2;
    turtle->y = renderer_h / 2;
    turtle->direction = SDLU_TURTLE_UP;

    turtle->r = turtle->g = turtle->b = turtle->a = 0xff;
    turtle->blendmode = SDL_BLENDMODE_NONE;
    turtle->drawing = 1;

    LL_PREPEND(turtles, turtle);

    return turtle;
}

int
SDLU_SetTurtleDrawColor(SDLU_Turtle* turtle, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    turtle->r = r;
    turtle->g = g;
    turtle->b = b;
    turtle->a = a;

    return 0;
}

int
SDLU_SetTurtleDrawBlendMode(SDLU_Turtle* turtle, SDL_BlendMode blendmode)
{
    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    turtle->blendmode = blendmode;

    return 0;
}

int
SDLU_SetTurtleDraw(SDLU_Turtle* turtle, int draw)
{
    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    turtle->drawing = draw;

    return 0;
}

int
SDLU_MoveTurtle(SDLU_Turtle* turtle, int steps)
{
    int x, y;
    Uint8 r, g, b, a;
    SDL_BlendMode blendmode;
    double rad;
    int result = 0;

    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    /** final position **/
    rad = (SDLU_PI / 180.0) * turtle->direction;
    x = SDLU_round((steps * SDL_cos(rad)) + turtle->x);
    y = SDLU_round((steps * SDL_sin(rad)) + turtle->y);

    if (turtle->drawing) {
        /** backup properties **/
        result |= SDL_GetRenderDrawColor(turtle->renderer, &r, &g, &b, &a);
        result |= SDL_GetRenderDrawBlendMode(turtle->renderer, &blendmode);

        /** draw line **/
        result |= SDL_SetRenderDrawColor(turtle->renderer, turtle->r, turtle->g, turtle->b, turtle->a);
        result |= SDL_SetRenderDrawBlendMode(turtle->renderer, turtle->blendmode);
        result |= SDL_RenderDrawLine(turtle->renderer, turtle->x, turtle->y, x, y);

        /** restore properties **/
        result |= SDL_SetRenderDrawColor(turtle->renderer, r, g, b, a);
        result |= SDL_SetRenderDrawBlendMode(turtle->renderer, blendmode);
    }

    /** update turtle position **/
    turtle->x = x;
    turtle->y = y;

    return result;
}

int
SDLU_RotateTurtle(SDLU_Turtle* turtle, int angle)
{
    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    turtle->direction += angle;

    return 0;
}

int
SDLU_SetTurtleDirection(SDLU_Turtle* turtle, int angle)
{
    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);
    
    turtle->direction = angle;
    
    return 0;
}

int
SDLU_SetTurtlePosition(SDLU_Turtle* turtle, int x, int y)
{
    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    if (turtle->drawing) {
        SDL_RenderDrawLine(turtle->renderer, turtle->x, turtle->y, x, y);
    }

    turtle->x = x;
    turtle->y = y;

    return 0;
}

int
SDLU_ResetTurtle(SDLU_Turtle* turtle)
{
    int renderer_w, renderer_h;

    if (turtle == NULL)
        SDLU_ExitError("invalid turtle", -1);

    SDL_GetRendererOutputSize(turtle->renderer, &renderer_w, &renderer_h);
    turtle->x = renderer_w / 2;
    turtle->y = renderer_h / 2;
    turtle->direction = SDLU_TURTLE_UP;
    turtle->drawing = 1;

    return 0;
}


int
SDLU_DestroyTurtle(SDLU_Turtle* turtle)
{
    LL_DELETE(turtles, turtle);
    SDLU_free(turtle);

    return 0;
}
