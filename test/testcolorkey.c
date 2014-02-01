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
 * testtexture: A test program for the SDL Utility library
 */

/* Tests texture loading functions */

#include "SDLU.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Texture* texture;           /* texture with colorkey    */
SDL_Texture* no_colorkey;       /* texture without colorkey */

/* cleanup function */
void cleanup( void ) {

    if (window) SDL_DestroyWindow( window );
    if (renderer) SDL_DestroyRenderer( renderer );
    if (texture) SDL_DestroyTexture( texture );
    if (no_colorkey) SDL_DestroyTexture( no_colorkey );

    SDL_Quit();
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    /* SDL initialization */
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit(cleanup);

    window = SDL_CreateWindow("testcolorkey", 100, 100, 400, 235, 0);
    SDL_CHECK( window );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_CHECK( renderer );

    no_colorkey = SDLU_LoadTexture(renderer, TUX_BMP);
    texture = SDLU_LoadTextureWithColorkey(renderer, TUX_BMP, SDLU_CreateRGB(255,0,255));
    SDL_CHECK( no_colorkey && texture );

    /*
     * render the textures and update the window
     */
    SDL_SetRenderDrawColor(renderer, SDLU_WHITE);
    SDL_RenderClear(renderer);

    SDLU_CopyTexture(renderer, texture, 0,0);
    SDLU_CopyTexture(renderer, no_colorkey, 200,0);

    SDL_RenderPresent(renderer);

    /*
     * the user should now see two tux's, one with colorkey and one without.
     *
     * wait until quit event
     */
    while( 1 ) {
        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            exit(0);
    }

    /* we never reach here */
    exit(0);
}
