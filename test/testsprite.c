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
 *  testsprite: A test program for the SDL Utility Library
 */

/* Tests SDLU sprite functionality */

#include "SDLU.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Event event;
SDL_bool done = SDL_FALSE;

SDLU_Sprite* sprite;
SDLU_Button* button;

/**
 *  cleanup function
 */
void cleanup(void)
{
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (sprite) SDLU_DestroySprite(sprite);
    if (button) SDLU_DestroyButton(button);
    if (texture) SDL_DestroyTexture(texture);
    SDL_Quit();
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    /* SDL Initialization */
    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO) != -1);
    atexit(cleanup);

    /* Create window and renderer */
    window = SDL_CreateWindow("testsprite", 100, 100, 640, 480, 0);
    SDL_CHECK(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_CHECK(renderer);
    SDL_RenderSetLogicalSize(renderer, 640, 480);

    /* create button */
    button = SDLU_CreateButton(window, "Exit", SDLU_BUTTON_TEXT);
    SDL_CHECK(button);
    SDLU_SetButtonGeometry(button, 250, 400, 140, -1);

    /* create the sprite */
    sprite = SDLU_CreateSpriteFromFile(renderer, GUY_BMP, 2);
    SDL_CHECK(sprite);
    SDLU_SetSpriteGeometry(sprite, 240, 140, -1, -1);
    SDLU_SetSpriteAdvance(sprite, 15);

    /** Init framerate manager **/
    SDLU_FPS_Init(45);

    while( !done ) {
        SDLU_FPS_Start();

        /* handle quit event */
        if ( SDL_PollEvent( &event ) ) {
            if (event.type == SDL_QUIT)
                done = SDL_TRUE;

            /* on button press */
            if (button->state == SDLU_PRESSED) {
                done = SDL_TRUE;
            }

            if (event.type == SDL_KEYDOWN)
            {
                /** pause/resume sprite **/
                if (event.key.keysym.sym == SDLK_RETURN) {
                    SDLU_PauseSprite(
                            sprite, sprite->is_paused ? 0 : 1
                    );
                }
            }
        }

        /** render the sprite in a white background **/
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, SDLU_WHITE);
        SDLU_RenderText(renderer, SDLU_ALIGN_CENTER, 40,
                "Press enter to pause/unpause the sprite");

        SDLU_RenderSprite(sprite);
        SDLU_RenderButton(button);

        SDL_SetRenderDrawColor(renderer, SDLU_BLACK);
        SDL_RenderPresent(renderer);

        SDLU_FPS_Cap();
    }
    exit(0);
}

