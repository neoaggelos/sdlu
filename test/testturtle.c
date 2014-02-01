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

/*
 * testturtle: A test program for the SDL Utility library
 */

/* Draw a rectangle with the turtle drawing API */

#include "SDLU.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_bool done = SDL_FALSE;
SDL_Event event;

/** called at exit to cleanup **/
void cleanup( void )
{
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv)
{
    /** Our turtle **/
    SDLU_Turtle* turtle;

    /** Initialize SDL **/
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit( cleanup );

    window = SDL_CreateWindow("", 100, 100, 320, 240, SDL_WINDOW_OPENGL);
    SDL_CHECK(window);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_CHECK(renderer);
    SDL_RenderSetLogicalSize(renderer, 320, 240);

    /** Create turtle **/
    turtle = SDLU_CreateTurtle(renderer);
    SDL_CHECK(turtle);

    /** main loop **/
    while( done == SDL_FALSE )
    {
        int i;

        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            done = SDL_TRUE;

        /** Clear screen **/
        SDL_RenderClear(renderer);

        /** Draw rectangle **/
        SDLU_ResetTurtle(turtle);

        for (i = 0; i < 4; i++) {
            SDLU_MoveTurtle(turtle, 100);
            SDLU_RotateTurtle(turtle, 90);
        }

        /** Update screen **/
        SDL_RenderPresent(renderer);
    }

    exit(0);
}

