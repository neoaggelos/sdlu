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
 * testcxx: A test program for the SDL Utility library
 */

/* Tests the C++ interface */

#include "SDLU.h"
#include <iostream>
#include <cstdlib>
#include "common.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

void buttonf(void* _this, void *_done)
{
    int* done = (int*)_done;
    std::cout << "Output from the callback" << std::endl;
    *done = SDL_TRUE;
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{

#ifdef SDLU_CXX /* if we have the C++ interface */

    /* objects */
    SDLU::Window* window;
    SDLU::Renderer* renderer;
    SDLU::Button* button;
    SDLU::Sprite* sprite;

    SDL_bool done = SDL_FALSE;
    SDL_Event event;

    /** initialize SDL **/
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );

    /** The arguments are the same of the original 'Create' functions **/
    window   = new SDLU::Window( "SDL2 Window", 100, 100, 400, 400, 0 );
    renderer = new SDLU::Renderer( window, SDL_RENDERER_ACCELERATED );
    button   = new SDLU::Button( window, "press to exit", SDLU_BUTTON_TEXT );
    sprite   = new SDLU::Sprite( renderer, GUY_BMP, 2 );

    window->SetTitle("Changed title");
    renderer->SetLogicalSize(400, 400);

    sprite->SetAdvance(15);
    sprite->SetGeometry(120, 40, -1, -1);

    button->SetGeometry(100, 280, 200, -1);
    button->SetAction(SDLU_HOVER_ACTION, SDLU_HOVER_BG|SDLU_HOVER_CURSOR);
    button->SetCallback(SDLU_PRESS_CALLBACK, buttonf, (void*)&done);

    /** initialize framerate counter **/
    SDLU_FPS_Init(50);
    while(!done)  {

        SDLU_FPS_Start();
        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            done = SDL_TRUE;

        renderer->Clear();          /**< SDL_RenderClear(renderer) **/

        sprite->Render();           /**< SDLU_RenderSprite(sprite) **/
        button->Render();           /**< SDLU_RenderButton(button) **/

        renderer->Present();        /**< SDL_RenderPresent(renderer) **/

        SDLU_FPS_Cap();
    }

    delete window, renderer, button, sprite;
    SDL_Quit();

    exit(0);

#else /* no SDLU_CXX */

    std::cout << "The C++ interface seems to not be available" << std::endl;
    exit(-1);

#endif
}

