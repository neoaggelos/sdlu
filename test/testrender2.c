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
 * testrender2: A test program for the SDL Utility library
 */

/* Mix pure OpenGL calls with the SDL2 Render API */

#include "SDLU.h"
#include "SDL_opengl.h"
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
    SDL_Rect sdl_rect = SDLU_CreateRect(100, 75, 120, 90);

    /** We want OpenGL **/
    SDL_SetHintWithPriority("SDL_RENDER_DRIVER", "opengl", SDL_HINT_OVERRIDE);

    /** Initialize SDL **/
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit( cleanup );

    window = SDL_CreateWindow("testrender2", 100, 100, 320, 240, SDL_WINDOW_OPENGL);
    SDL_CHECK(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_CHECK(renderer);

    /** wait for quit event **/
    while( done == SDL_FALSE )
    {
        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            done = SDL_TRUE;

        /** SDL Rendering **/
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xff, 0x88, 0x00, 0xff);
        SDL_RenderDrawRect(renderer, &sdl_rect);

        /** OpenGL Rendering **/
        SDLU_GL_RenderCacheState(renderer);
        glShadeModel(GL_SMOOTH);

        glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0); glVertex2f(160, 75);
            glColor3f(0, 0, 1); glVertex2f(100, 165);
            glColor3f(0, 1, 0); glVertex2f(220, 165);
        glEnd();

        glShadeModel(GL_FLAT);      /* restore state */
        SDLU_GL_RenderRestoreState(renderer);

        /** Update screen **/
        SDL_RenderPresent(renderer);
    }

    exit(0);
}

