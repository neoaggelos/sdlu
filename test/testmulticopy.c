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
 * testmulticopy: A test program for the SDL Utility library
 */

/* Tests SDLU_RenderMultiCopy */

#include "SDLU.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Texture* texture;
SDL_Rect r = {0, 0, 64, 64 };

void cleanup( void ) {
    if (window) SDL_DestroyWindow( window );
    if (renderer) SDL_DestroyRenderer( renderer );
    if (texture) SDL_DestroyTexture( texture );

    SDL_Quit();
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    /* SDL Initialization */
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit( SDL_Quit );

    window = SDL_CreateWindow( "testmulticopy", 100, 100, 512, 512, 0);
    SDL_CHECK( window );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_CHECK( renderer );

    texture = SDLU_LoadTexture(renderer, TILE_BMP);
    SDL_CHECK( texture );

    /* Drawing */
    SDL_RenderClear(renderer);

    while (r.y < 512) {

        SDLU_RenderMultiCopy(
            renderer,                   /* renderer to draw         */
            texture,                    /* source texture           */
            NULL,                       /* source rect              */
            &r,                         /* dest rect                */
            8,                          /* loop 8 times             */
            "x+64"                      /* adjust destination rect  */
        );

        /* move down 64 for the new row */
        r.y += 64;

    }

    /* Update window */
    SDL_RenderPresent(renderer);

    while( 1 ) {
        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            break;
    }

    exit(0);
}
