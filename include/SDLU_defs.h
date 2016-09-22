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

/**
 *  \file SDLU_defs.h
 *
 *  \brief Defines all SDLU structures.
 */

#ifndef SDLU_DEFS_H
#define SDLU_DEFS_H

#include "SDL.h"
#include "SDLU_font.h"
#include "begin_code.h"

/**
 *  \name Alignment macros
 *
 *  \brief This macros can be passed wherever a function requests (x,y)
 *  coordinates to align the output.
 */
/*@{*/
#define SDLU_ALIGN_LEFT     -10000
#define SDLU_ALIGN_RIGHT    -10001
#define SDLU_ALIGN_CENTER   -10002
#define SDLU_ALIGN_TOP      -10000
#define SDLU_ALIGN_BOTTOM   -10001
/*@}*/

typedef struct SDLU_Circle SDLU_Circle;
typedef struct SDLU_Button SDLU_Button;
typedef struct SDLU_Sprite SDLU_Sprite;

/**
 *  \name Common color macros
 *
 *  You can use them like this:
 *  \code
 *      SDLU_SetRenderDrawColor(renderer, SDLU_WHITE);
 *      // expands to SDLU_SetRenderDrawColor(renderer, 255,255,255,255);
 *  \endcode
 *
 *  The macros suffixed with `_RGB` should be used when you do not need the
 *  alpha value
 */
/*@{*/
#define SDLU_RED_RGB        200,   0,   0
#define SDLU_GREEN_RGB        0, 200,   0
#define SDLU_BLUE_RGB         0,   0, 200
#define SDLU_ORANGE_RGB     255, 128,   0
#define SDLU_MAGENTA_RGB    255,   0, 255
#define SDLU_YELLOW_RGB     255, 255,   0
#define SDLU_WHITE_RGB      255, 255, 255
#define SDLU_GRAY_RGB       150, 150, 150
#define SDLU_BLACK_RGB        0,   0,   0

#define SDLU_RED        SDLU_RED_RGB,     255
#define SDLU_GREEN      SDLU_GREEN_RGB,   255
#define SDLU_BLUE       SDLU_BLUE_RGB,    255
#define SDLU_ORANGE     SDLU_ORANGE_RGB,  255
#define SDLU_MAGENTA    SDLU_MAGENTA_RGB, 255
#define SDLU_YELLOW     SDLU_YELLOW_RGB,  255
#define SDLU_WHITE      SDLU_WHITE_RGB,   255
#define SDLU_GRAY       SDLU_GRAY_RGB,    255
#define SDLU_BLACK      SDLU_BLACK_RGB,   255
/*@}*/

/**
 *  \brief callback prototype
 *
 *  \param _this The object that calls the callback (button or a combobox)
 *  \param userdata void* pointer for user data
 *
 *  \sa SDLU_SetButtonCallback()
 *  \sa SDLU_SetComboBoxCallback()
 */
typedef void (SDLCALL * SDLU_Callback) (void* _this, void* userdata);

/**
 * \brief styles for gui components (e.g. SDLU_Button or SDLU_ComboBox)
 *
 * \sa SDLU_GetButtonStyles()
 * \sa SDLU_GetDefaultStyles()
 */
typedef struct {
    const char*     title;          /**< label                  **/
    SDLU_Font*      font;           /**< font                   **/
    SDL_Color       text_color;     /**< text color             **/
    SDL_Color       fill_color;     /**< fill color             **/
    SDL_Color       box_color;      /**< box color              **/
    SDL_BlendMode   blendmode;      /**< blendmode              **/
} SDLU_Styles;

/**
 *  \brief Get default styles for gui components
 */
extern DECLSPEC SDLU_Styles* SDLCALL SDLU_GetDefaultStyles();

/**
 *  \brief The button structure
 */
struct SDLU_Button {
    Uint32 id;                      /**< unique identifier -- READONLY  **/
    Uint32 flags;                   /**< button flags                   **/
    SDL_Window * window;            /**< parent window                  **/

    const char* name;               /**< application-defined identifier **/
    void *unused;                   /**< user data                      **/

    void* content;                  /**< button content [text or image] **/
    SDL_Rect rect;                  /**< size and position              **/
    int (*render)(SDLU_Button*);    /**< render function of the button  **/

    Uint32 state;                   /**< current button state           **/
    SDLU_Callback callback[2];      /**< button callbacks               **/
    void* arg[2];                   /**< arguments for callbacks        **/
    int action[2];                  /**< press and hover actions        **/

    SDL_Scancode hotkey;            /**< button hotkey                  **/

    SDLU_Button* next;              /**< DO NOT TOUCH                   **/
};

/**
 *  \brief The SDLU_Circle structure
 */
struct SDLU_Circle {
    int x, y;                   /**< coordinates of the circle's center **/
    int r;                      /**< radius                             **/
};

/**
 * \brief internal counter, used by SDLU_Sprite
 */
typedef struct {
    int max;
    int index;
} SDLU_Counter;

/**
 *  \brief The SDLU sprite structure
 */
struct SDLU_Sprite {
    Uint32 id;                      /**< unique identifier                  **/

    SDLU_Counter frames;            /**< number of sprite frames            **/
    SDLU_Counter advance;           /**< frame refresh counter              **/

    double xvel, yvel;              /**< velocity (for X and Y)             **/
    double xoffset, yoffset;        /**< difference of the on-screen/actual
                                      position of the sprite                **/

    double direction;               /**< direction (0 is the default)       **/
    int know_direction;             /**< whether we know the current
                                      direction of the sprite               **/

    int is_paused;                  /**< whether the sprite is paused       **/
    int mode;                       /**< SDLU_VERTICAL or SDLU_HORIZONTAL   **/

    int draw_rotated;               /**< whether the sprite should be
                                      drawn rotated                         **/

    SDL_Renderer * renderer;        /**< associated renderer                **/
    SDL_Texture * data;             /**< texture containing all frames      **/
    SDL_Rect rect;                  /**< position of the sprite             **/
    SDL_Rect map;                   /**< the current sprite map             **/

    int (*update)(SDLU_Sprite *);   /**< user-defined update function       **/
    int (*move)  (SDLU_Sprite *);   /**< moves the sprite                   **/
    int (*render)(SDLU_Sprite *);   /**< sprite render function             **/

    void * unused;                  /**< handler for userdata               **/

    SDLU_Sprite *next;              /**< DO NOT TOUCH **/
};

/**
 *  \name SDLU sprite modes
 *
 *  \brief These macros indicate how the frames of the sprite are arranged
 */
/*@{*/
#define SDLU_HORIZONTAL 0x00000001  /**< the frames are in the same row     **/
#define SDLU_VERTICAL   0x00000002  /**< the frames are in the same column  **/
/*@}*/

#include "close_code.h"

#endif /* SDLU_DEFS_H */


