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

/*
 * testrender: A test program for the SDL Utility library
 */

/* Tests rendering functions */

#include "SDLU.h"
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

void cleanup( void ) {
    if (window) SDL_DestroyWindow( window );
    if (renderer) SDL_DestroyRenderer( renderer );

    SDL_Quit();
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{

    /* SDL initialization */
    SDL_CHECK( SDL_Init( SDL_INIT_VIDEO ) != -1 );
    atexit(cleanup);

    window = SDL_CreateWindow( "testrender", 100, 100, 400, 400, 0 );
    SDL_CHECK( window );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_CHECK( renderer );

    /*
     * render pentagon
     */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDLU_RenderBegin(SDLU_FILL);                 /* start */
        SDLU_RenderSetPoint(200, 100);
        SDLU_RenderSetPoint(300, 170);
        SDLU_RenderSetPoint(250, 300);
        SDLU_RenderSetPoint(150, 300);
        SDLU_RenderSetPoint(100, 170);
    SDLU_RenderEnd(renderer);           /* render the polygon */

    /*
     * render circle
     */
    SDL_SetRenderDrawColor( renderer, 0, 0, 150, 255);
    SDLU_RenderDrawCircle(renderer, 200, 207, 107);

    /*
     * update display and quit
     */
    SDL_RenderPresent(renderer);

    while( 1 ) {
        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            break;
    }

    exit(0);
}


