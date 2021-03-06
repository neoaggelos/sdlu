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
 * testtext: A test program for the SDL Utility library
 */

/* Tests the text rendering functions */

#include "SDLU.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_bool done = SDL_FALSE;

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
    /** Initialize SDL **/
    SDL_CHECK( SDL_Init( SDL_INIT_VIDEO ) != -1 );
    atexit( cleanup );

    /** Create window **/
    window = SDL_CreateWindow("testtext", 100, 100, 640, 480, 0);
    SDL_CHECK(window);

    /** Create renderer **/
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_CHECK(renderer);

    /** Start main loop **/
    while(!done) {

        /** Handle SDL_QUIT **/
        if (SDL_PollEvent(&event), event.type == SDL_QUIT) {
            done = SDL_TRUE;
        }

        /** Clear screen **/
        SDL_RenderClear(renderer);

        /** We want white text in black background **/
        SDL_SetRenderDrawColor( renderer, SDLU_WHITE );

        /** Aligned text **/
        SDLU_RenderText(
                renderer, SDLU_ALIGN_RIGHT, SDLU_ALIGN_TOP,
                "Text aligned in the top-right corner"
        );

        /** printf-format **/
        SDLU_RenderText(
                renderer, SDLU_ALIGN_CENTER, 100,
                "100 + 100 = %d", 100 + 100
        );

        /** Different colors **/
        SDL_SetRenderDrawColor(renderer, SDLU_RED);
        SDLU_RenderText( renderer, 0, 0, "Red colored text" );

        /** custom font **/
        SDLU_SetTruetypeFontFile(FONT_TTC, 20);
        SDLU_RenderText( renderer, 250, 250, "Custom font");
        SDLU_SetTruetypeFont(NULL);     /** reset **/

        /** Update the screen **/
        SDL_SetRenderDrawColor(renderer, SDLU_BLACK);
        SDL_RenderPresent(renderer);
    }
    exit(0);
}
