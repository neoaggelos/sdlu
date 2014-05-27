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
 * testcombo: A test program for the SDL utility library
 */

/*
 * Working with combo box buttons
 */

#include "SDLU.h"
#include "common.h"
#include <stdlib.h>

const char* choice = "";

/**
 * this is the callback that is executed when a new item is chosen
 */
void
callback(void* _this, void* unused)
{
    SDLU_ComboBox* this = (SDLU_ComboBox*) _this;
    choice = this->current;
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDLU_ComboBox* combobox;

    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO) != -1);
    atexit(SDL_Quit);

    window = SDL_CreateWindow("testcombo", 100, 100, 320, 240, 0);
    SDL_CHECK(window);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_CHECK(renderer);
    SDL_RenderSetLogicalSize(renderer, 320, 240);

    /* create combobox */
    combobox = SDLU_CreateComboBox(window);
    SDL_CHECK(combobox);

    /** initialize combobox **/
    SDLU_SetComboBoxCallback(combobox, callback, NULL);
    SDLU_SetComboBoxGeometry(combobox, 85, 30, 150, 35);

    SDLU_AddComboBoxItem(&combobox, "Greece");
    SDLU_AddComboBoxItem(&combobox, "USA");
    SDLU_AddComboBoxItem(&combobox, "Spain");
    SDLU_AddComboBoxItem(&combobox, "Argentina");

    while(SDL_PollEvent(&event), event.type != SDL_QUIT) {
        SDL_SetRenderDrawColor(renderer, SDLU_BLACK);
        SDL_RenderClear(renderer);

        SDLU_RenderComboBox(combobox);

        SDL_SetRenderDrawColor(renderer, SDLU_WHITE);
        SDLU_RenderText(renderer, SDLU_ALIGN_CENTER, 200,
                "Your choice is %s", choice);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    exit(0);
}
