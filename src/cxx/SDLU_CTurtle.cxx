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

SDLU::Turtle::Turtle(void)
{
    this->turtle = NULL;
}

SDLU::Turtle::Turtle(SDL_Renderer* renderer)
{
    this->turtle = SDLU_CreateTurtle(renderer);
}

SDLU::Turtle::Turtle(SDLU::Renderer* renderer)
{
    this->turtle = SDLU_CreateTurtle(renderer->GetRenderer());
}

SDLU::Turtle::Turtle(SDLU_Turtle* turtle)
{
    this->turtle = turtle;
}

SDLU::Turtle::~Turtle(void)
{
    SDLU_DestroyTurtle(this->turtle);
}

int SDLU::Turtle::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDLU_SetTurtleDrawColor(this->turtle, r, g, b, a);
}

int SDLU::Turtle::SetDrawBlendMode(SDL_BlendMode blendmode)
{
    return SDLU_SetTurtleDrawBlendMode(this->turtle, blendmode);
}

int SDLU::Turtle::Move(int steps)
{
    return SDLU_MoveTurtle(this->turtle, steps);
}

int SDLU::Turtle::SetPosition(int x, int y)
{
    return SDLU_SetTurtlePosition(this->turtle, x, y);
}

int SDLU::Turtle::Rotate(double angle)
{
    return SDLU_RotateTurtle(this->turtle, angle);
}

int SDLU::Turtle::Reset(void)
{
    return SDLU_ResetTurtle(this->turtle);
}

int SDLU::Turtle::SetDirection(double angle)
{
    return SDLU_SetTurtleDirection(this->turtle, angle);
}
