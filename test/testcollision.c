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
 * testcollision: A test program for the SDL Utility library
 */

/* Tests collision detection between two rectangles */

#include "SDLU.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/*
 * desired framerate: 20 because we want to be slow.
 */
#define FPS 20

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Rect a, b;

/*
 * cleanup function
 */
void
cleanup( void )
{
	if (window) 	SDL_DestroyWindow  (  window  );
	if (renderer) 	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    int i = 0;
    char *msg;

    /* SDL initialization */
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
	atexit(cleanup);

    window = SDL_CreateWindow( "testcollision", 100, 100, 500, 500, 0 );
    SDL_CHECK( window );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_CHECK( renderer );

    /* the two rectangles */
	a.x = 0;
	a.y = 100;
	a.w = 100;
	a.h = 100;

	b.x = 400;
	b.y = 100;
	b.w = 100;
	b.h = 100;

    /*
     * set the text to SDLU_MEDIUM, to get more clear output
     */
    SDLU_SetFontSize( SDLU_TEXT_SIZE_MEDIUM );

    /*
     * initialize the framerate counter
     * just before the main loop
     */
    SDLU_FPS_Init(FPS);

    /*
     * SDLU_CollideRects( SDL_Rect a , SDL_Rect b )
     *  Returns a positive value if there is collision, 0 otherwise.
     *
     * The returned value can be also used to identify the type of the collision
     * see below.
     *
     * repeat while there is no collision
     * keep the result in 'i'
     */
	while ( (i = SDLU_CollideRects(a,b)) == 0)
	{
        /*
         * start the fps counter
         */
		SDLU_FPS_Start();

        /* press any key to toggle framerate capping */
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
            exit(0);

        /*
         * SDLU_FPS_ToggleCap() toggles whether or not we want to cap the
         * framerate.
         *
         * To see its effect, just press any button while executing the
         * application.
         */
        if (event.type == SDL_KEYDOWN)
            SDLU_FPS_ToggleCap();

        /* update position */
		a.x += 1;
		b.x -= 1;
		a.y += 1;
		b.y += 1;

		SDL_RenderClear(renderer);

        /*
         * Write the framerate message
         */
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDLU_RenderText(renderer,
                        SDLU_ALIGN_RIGHT, SDLU_ALIGN_TOP,
                        "FPS: %d", SDLU_FPS_GetRealFramerate());

        /*
         * render the two rectangles
         */
		SDL_SetRenderDrawColor(renderer, 255, 0,0,100);
		SDL_RenderDrawRect(renderer, &a);
		SDL_SetRenderDrawColor(renderer, 0,0,255,100);
		SDL_RenderDrawRect(renderer, &b);
		SDL_SetRenderDrawColor(renderer,0,0,0,0);

        /*
         * update display
         */
		SDL_RenderPresent(renderer);

        /*
         * cap the framerate
         */
		SDLU_FPS_Cap();
	}

    /*
     * check the kind of the collision
     */
	if (i == SDLU_COLLIDE_VERTICAL)
        msg = "The collision was vertical";
	if (i == SDLU_COLLIDE_HORIZONTAL)
        msg = "The collision was horizontal";

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
            "Collision Detected!", msg, NULL);

    exit(0);
}
