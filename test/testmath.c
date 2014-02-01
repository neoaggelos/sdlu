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
 * testmath: A test program for the SDL Utility library
 */

/*
 * Working with vectors
 */

#include "SDLU.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Window position **/
#define winx SDL_WINDOWPOS_CENTERED
#define winy SDL_WINDOWPOS_CENTERED

/** Positions for 2D axis system **/
#define ORIGIN_X 20
#define ORIGIN_Y 20

/* draw the x and y axes */
void draw_axes(SDL_Renderer* renderer)
{
    const int x = 300, y = 220;
    SDL_SetRenderDrawColor(renderer, SDLU_WHITE);
    
    SDL_RenderDrawLine(renderer, ORIGIN_X, ORIGIN_Y, x, ORIGIN_Y); /* x axis */
    SDL_RenderDrawLine(renderer, ORIGIN_X, ORIGIN_Y, ORIGIN_X, y); /* y axis */
}


/* draws a vector in a 2D space */
void draw_vector(SDL_Renderer* renderer, SDLU_Vector *v)
{
    SDL_RenderDrawLine(renderer, 
            ORIGIN_X, ORIGIN_Y, 
            ORIGIN_X + v->x, ORIGIN_Y + v->y);
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool done = SDL_FALSE;

    SDLU_Vector a, b, c;

    /** SDL Initialization **/
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit(SDL_Quit);

    /** Create the window and the renderer **/
    window = SDL_CreateWindow("testmath", winx, winy, 320, 240, 0);
    SDL_CHECK(window);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, 320, 240);
    SDL_CHECK(renderer);

    a = SDLU_NewVector(140, 50, 0, 0);
    b = SDLU_NewVector(30, 142, 0, 0);

    SDLU_AddVectors(a, b, &c);

    /** Enter the main loop **/
    while( !done )
    {
        SDL_Event event;

        /** Handle SDL_QUIT **/
        if (SDL_PollEvent(&event), event.type == SDL_QUIT) {
            done = SDL_TRUE;
        }

        /** Render the scene **/
        SDL_SetRenderDrawColor(renderer, SDLU_BLACK);
        SDL_RenderClear(renderer);

        draw_axes(renderer);

        SDL_SetRenderDrawColor(renderer, SDLU_RED);
        draw_vector(renderer, &a);

        SDL_SetRenderDrawColor(renderer, SDLU_BLUE);
        draw_vector(renderer, &b);

        SDL_SetRenderDrawColor(renderer, SDLU_MAGENTA);
        draw_vector(renderer, &c);

        /** Update screen **/
        SDL_RenderPresent(renderer);

        /** Delay a minimum amount of time to let the CPU rest **/
        SDL_Delay(2);
    }

    /** Do some clean-up **/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /** Exit **/
    exit(0);
}
