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
 * testbutton: A test program for the SDL Utility library
 */

/*
 * The classic example with two buttons ('+' and '-') adding or substracting
 * to a value, using button callbacks
 */

#include "SDLU.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>

/** Window position **/
#define winx SDL_WINDOWPOS_CENTERED
#define winy SDL_WINDOWPOS_CENTERED

/** Button actions (NOT callbacks) **/
#define press_action SDLU_PRESS_INVERT                 /** invert button colors on press **/
#define hover_action SDLU_HOVER_CURSOR | SDLU_HOVER_BG /** change cursor and background color on hover **/

/**
 *  callback function for the help button
 */
void help_dialog(void* _this, void* unused)
{
    SDLU_Button* this = (SDLU_Button*) _this;

    SDL_ShowSimpleMessageBox(
            0,
            "Help",
            "Use the '+' and '-' buttons to add or substract 1 to the value\n"
            "on the right. Use 'reset' to reset the value to 0.\n"
            "Press 'exit' to exit",
            this->window
    );
}

/**
 *  callback function for the buttons
 *
 *  the identifier we store at 'button->name' will tell us which button has
 *  been pressed. if it is 'add', then we add 1 to the sum, and if it is 'minus'
 *  we substract 1
 */
void button_callback(void* _this, void* _arg)
{
    SDLU_Button* this = (SDLU_Button*) _this;

    if (strcmp(this->name, "add") == 0) {
        /** '+' button **/
        int *sum = (int*)_arg;
        *sum += 1;
    } else if (strcmp(this->name, "sub") == 0) {
        /** '-' button **/
        int *sum = (int*)_arg;
        *sum -= 1;
    } else if (strcmp(this->name, "reset") == 0) {
        /** 'reset' button **/
        int *sum = (int*)_arg;
        *sum = 0;
    } else if (strcmp(this->name, "exit") == 0) {
        /** 'exit' button */
        SDL_bool *done = (SDL_bool*)_arg;
        *done = SDL_TRUE;
    }
}

/**
 *  automatically add the SDLU_BUTTON_ROUND flag to button creation
 */
SDLU_Button* 
SDLU_CreateRoundButton(SDL_Window* window, void* data, Uint32 flags)
{
    return SDLU_CreateButton(window, data, flags | SDLU_BUTTON_ROUND);
}

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDLU_Button *plus, *minus, *reset, *quit, *help;
    SDL_bool done = SDL_FALSE;
    int sum = 0;

    /* help button graphics */
    SDL_Texture* help_tex;

    /** SDL Initialization **/
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit(SDL_Quit);

    /** Create the window and the renderer **/
    window = SDL_CreateWindow("testbutton", winx, winy, 320, 240, 0);
    SDL_CHECK(window);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, 320, 240);
    SDL_CHECK(renderer);

    /** Create the '+' button **/
    plus = SDLU_CreateRoundButton(window, "+", SDLU_BUTTON_TEXT);
    SDL_CHECK(plus);
    plus->name = "add";                     /** store the button identifier **/
    SDLU_SetButtonGeometry(plus, 50, 40, 100, 30);
    SDLU_SetButtonAction(plus, SDLU_PRESS_ACTION, press_action);
    SDLU_SetButtonAction(plus, SDLU_HOVER_ACTION, hover_action);
    SDLU_SetButtonCallback(plus, SDLU_PRESS_CALLBACK, button_callback, &sum);

    /** Create the '-' button **/
    minus = SDLU_CreateRoundButton(window, "-", SDLU_BUTTON_TEXT);
    SDL_CHECK(minus);
    minus->name = "sub";                    /** store the button identifier **/
    SDLU_SetButtonGeometry(minus, 50, 110, 100, 30);
    SDLU_SetButtonAction(minus, SDLU_PRESS_ACTION, press_action);
    SDLU_SetButtonAction(minus, SDLU_HOVER_ACTION, hover_action);
    SDLU_SetButtonCallback(minus, SDLU_PRESS_CALLBACK, button_callback, &sum);

    /** Create the 'reset' button **/
    reset = SDLU_CreateRoundButton(window, "Reset", SDLU_BUTTON_TEXT);
    SDL_CHECK(reset);
    reset->name = "reset";                  /** store the button identifier **/
    SDLU_SetButtonGeometry(reset, 10, 190, 120, 30);
    SDLU_SetButtonAction(reset, SDLU_PRESS_ACTION, press_action);
    SDLU_SetButtonAction(reset, SDLU_HOVER_ACTION, hover_action);
    SDLU_SetButtonCallback(reset, SDLU_PRESS_CALLBACK, button_callback, &sum);

    /** Create the 'quit' button **/
    quit = SDLU_CreateRoundButton(window, "Exit", SDLU_BUTTON_TEXT);
    SDL_CHECK(quit);
    quit->name = "exit";                    /** store the button identifier **/
    SDLU_SetButtonGeometry(quit, 190, 190, 120, 30);
    SDLU_SetButtonAction(quit, SDLU_PRESS_ACTION, press_action);
    SDLU_SetButtonAction(quit, SDLU_HOVER_ACTION, hover_action);
    SDLU_SetButtonCallback(quit, SDLU_PRESS_CALLBACK, button_callback, &done);

    help_tex = SDLU_LoadTexture(renderer, HELP_BMP);
    SDL_CHECK(help_tex);

    /** Create the 'help' button **/
    help = SDLU_CreateButton(window, help_tex, SDLU_BUTTON_IMAGE);
    SDL_CHECK(help);
    help->name = "help";
    SDLU_SetButtonGeometry(help, 144, 187, 32, 32);
    SDLU_SetButtonAction(help, SDLU_HOVER_ACTION, hover_action);
    SDLU_SetButtonCallback(help, SDLU_PRESS_CALLBACK, help_dialog, NULL);

    /** Enter the main loop **/
    while( !done )
    {
        SDL_Event event;

        /** Handle SDL_QUIT **/
        if (SDL_PollEvent(&event), event.type == SDL_QUIT) {
            done = SDL_TRUE;
        }

        /** Render the scene **/
        SDL_RenderClear(renderer);

        /** Render buttons **/
        SDLU_RenderButton(plus);
        SDLU_RenderButton(minus);
        SDLU_RenderButton(reset);
        SDLU_RenderButton(quit);
        SDLU_RenderButton(help);

        /** Render the sum **/
        SDL_SetRenderDrawColor(renderer, SDLU_WHITE);
        SDLU_RenderText(renderer, 230, 80, "%d", sum);

        /** render a rectangle around the '+' and '-' buttons **/
        do {
            SDL_Rect rect = {10, 20, 300, 145};
            SDL_RenderDrawRect(renderer, &rect);
        } while(0);

        /** reset color to black **/
        SDL_SetRenderDrawColor(renderer, SDLU_BLACK);

        /** Update screen **/
        SDL_RenderPresent(renderer);

        /** Delay a minimum amount of time to let the CPU rest **/
        SDL_Delay(2);
    }

    /** Do some clean-up **/
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(help_tex);
    SDLU_DestroyButton(plus);
    SDLU_DestroyButton(minus);
    SDLU_DestroyButton(quit);
    SDLU_DestroyButton(reset);
    SDLU_DestroyButton(help);

    /** Exit **/
    exit(0);
}
