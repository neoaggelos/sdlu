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

/**
 *  \file SDLU_button.h
 *
 *  \brief Defines the functions for manipulating button entities
 *
 *  Buttons in SDLU support press and hover callbacks, different built-in
 *  behaviours when pressed or hovered [called actions], and can be fully
 *  customized.
 */

#ifndef SDLU_BUTTON_H
#define SDLU_BUTTON_H

#include "SDLU_defs.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \name SDLU_button state macros.
 *
 *  \brief These are returned to indicate the state of the button
 */
/*@{*/
#define SDLU_IDLE       0x00  /**< No activity for the button   **/
#define SDLU_PRESSED    0x01  /**< The button is pressed        **/
#define SDLU_HOVERED    0x02  /**< The button is hovered        **/
/*@}*/

/**
 *  \name Button Event IDs
 */
/*@{*/
#define SDLU_BUTTON_HOVER SDLU_GetButtonHoverEvent()
    /**< a button has been hovered **/
#define SDLU_BUTTON_PRESS SDLU_GetButtonPressEvent()
    /**< a button has been pressed **/
#define SDLU_BUTTON_RELEASE SDLU_GetButtonReleaseEvent()
    /**< a button has been released (it's no more pressed) **/
#define SDLU_BUTTON_LOSTFOCUS SDLU_GetButtonLostFocusEvent()
    /**< a button has lost focus (it's no more hovered) **/
/*@}*/

/**
 *  \name Available button action types
 *
 *  \sa SDLU_SetButtonAction()
 */
/*@{*/
#define SDLU_PRESS_ACTION 0x00 /**< button action on press **/
#define SDLU_HOVER_ACTION 0x01 /**< button action on hover **/
/*@{*/

/**
 *  \name Available hover actions
 *
 *  \sa SDLU_SetButtonAction()
 */
/*@{*/
#define SDLU_HOVER_NONE             0x00000000 /**< no hover action  **/
#define SDLU_HOVER_BG               0x00000001 /**< background color **/
#define SDLU_HOVER_FG               0x00000002 /**< foreground color **/
#define SDLU_HOVER_UL               0x00000004 /**< underline text   **/
#define SDLU_HOVER_CURSOR           0x00000008 /**< change cursor    **/
/*@}*/

/**
 *  \name Available press actions
 *
 *  \sa SDLU_SetButtonAction()
 */
/*@{*/
#define SDLU_PRESS_NONE             0x00000000 /**< no press action      **/
#define SDLU_PRESS_INVERT           0x00000001 /**< invert button colors **/
/*@}*/

/**
 *  \name Button creation flags
 */
/*@{*/
#define SDLU_BUTTON_TEXT    0x01 /**< Indicates a text button **/
#define SDLU_BUTTON_IMAGE   0x02 /**< Indicates an image button **/
#define SDLU_BUTTON_THEMED  0x04 /**< The button image is themed.
                                  See SDLU_CreateButton() **/
#define SDLU_BUTTON_HIDDEN  0x08 /**< The button is hidden **/
#define SDLU_BUTTON_ROUND   0x10 /**< The button has round corners **/
#define SDLU_BUTTON_FOREIGN 0x20 /**< The button does not use the SDL2 Render
                                   API for rendering, see SDLU_CreateButton()
                                   for more information **/
/*@}*/

/**
 *  \brief Creates a new push button
 *
 *  Buttons in SDLU can be either text or image buttons. Both are handled by the
 *  same structure. Upon creation, you choose what button type you want with the
 *  'flags' parameter. 'flags' MUST contain at least one of SDLU_BUTTON_TEXT or
 *  SDLU_BUTTON_IMAGE. The former indicates a text button, whereas the latter an
 *  image button. You can pass two or more flags OR'd together.
 *
 *  Note that depending on the button type you choose, the second parameter is
 *  handled differently, as shown by the table below:
 *
 *  | flag                  | Button type       | Expected 'data' type      |
 *  |-----------------------|-------------------|---------------------------|
 *  | SDLU_BUTTON_TEXT      | text              | const char *              |
 *  | SDLU_BUTTON_IMAGE     | image             | SDL_Texture *             |
 *
 *  If you pass the wrong type, then it's quite possible that a segfault will
 *  occur. See the code examples below:
 *
 *  \code
 *  // These are perfectly valid examples
 *  SDLU_Button* b = SDLU_CreateButton(sdl_window, "text", SDLU_BUTTON_TEXT);
 *  SDLU_Button* b = SDLU_CreateButton(sdl_win, sdl_texture, SDLU_BUTTON_IMAGE);
 *  SDLU_Button* b = SDLU_CreateButton(
 *      sdl_window, sdl_texture, SDLU_BUTTON_IMAGE | SDLU_BUTTON_HIDDEN
 *  );
 *
 *  // These will most likely cause segfaults
 *  SDLU_Button* b = SDLU_CreateButton(sdl_win, sdl_texture, SDLU_BUTTON_TEXT);
 *  SDLU_Button* b = SDLU_CreateButton(sdl_win, "text", SDLU_BUTTON_IMAGE);
 *
 *  // This is by default avoided for safety reasons
 *  SDLU_Button* b = SDLU_CreateButton(
 *          sdl_window, data, SDLU_BUTTON_TEXT | SDLU_BUTTON_IMAGE
 *  );
 *  \endcode
 *
 *  About SDLU_BUTTON_THEMED: By default, buttons whose content is an
 *  'SDL_Texture*' are considered to have the same appearence when
 *  they are idle/hovered/pressed [Think of it like a plain image]. But what if
 *  you want an image button whose appearence changes when it is hovered or
 *  pressed? That's why SDLU_BUTTON_THEMED is there.
 *
 *  About SDLU_BUTTON_FOREIGN: Normally, the buttons are rendered using the SDL2
 *  Render API. However, due to the limitations of the Rendering API, many
 *  application developers choose to use OpenGL (ES) directly. To make it
 *  possible to use the Button API under such occasions, this flag may be used.
 *  Note that in that case [at least for now],, you will have to take care of 
 *  writing the functions to render the button, see SDLU_SetButtonRenderFunc().
 *
 *  If passed along with SDLU_BUTTON_IMAGE, SDLU_BUTTON_THEMED tells the library
 *  that the image given actually contains three instances of the button: one
 *  when idle, one when pressed and one when hovered. The image format should be
 *  this:
 *
 *  \code
 *   _______________________________________________
 *  |               |               |               |
 *  |     idle      |    hovered    |    pressed    |
 *  |_______________|_______________|_______________|
 *   \_____ w _____/ \_____ w _____/ \_____ w _____/
 *
 *  \endcode
 *
 *  ... and the appropriate image is displayed automatically depending on the
 *  current button state [idle/pressed/hovered].
 *
 *  \param window The associated window
 *  \param data The button data
 *  \param flags A mask of 'SDLU_BUTTON_*' flags OR'd together
 *
 *  \return A new push button or NULL on error
 *
 *  \note SDLU_BUTTON_TEXT | SDLU_BUTTON_IMAGE as flags parameter is not
 *  allowed, and will produce an error.
 *
 *  \sa SDLU_Button
 *  \sa SDLU_DestroyButton()
 *  \sa SDLU_BUTTON_TEXT
 *  \sa SDLU_BUTTON_IMAGE
 *  \sa SDLU_BUTTON_HIDDEN
 *  \sa SDLU_BUTTON_THEMED
 *  \sa SDLU_HINT_BUTTON_PUSH_EVENTS
 */
extern DECLSPEC SDLU_Button* SDLCALL SDLU_CreateButton(
        SDL_Window* window, const void* data, Uint32 flags
);

/**
 *  \brief Get a button from its id
 *
 *  \param id The unique identifier of the requested button
 *
 *  \return The requested button if id is valid, NULL otherwise.
 */
extern DECLSPEC SDLU_Button* SDLCALL SDLU_GetButtonFromID(Uint32 id);

/**
 *  \brief Get the button initialization flags
 *
 *  \param button Button to query
 *
 *  \return The button flags on success, 0 on error
 */
extern DECLSPEC Uint32 SDLCALL SDLU_GetButtonFlags(SDLU_Button* button);

/**
 *  \brief Set the size and position of a button
 *
 *  \param button Button to update
 *  \param x,y (x,y) coordinates of the button, -1 to keep old position
 *  \param w,h width and height of the button, -1 to keep old size
 *
 *  \return 0 on success, -1 on error.
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonGeometry(
        SDLU_Button* button,
        int x, int y,
        int w, int h
);

/**
 *  \brief Get the button position/size
 *
 *  \param button Button to query
 *  \param x,y Will be filled with the button's position
 *  \param w,h Will be filled with the button's size
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetButtonGeometry(
        SDLU_Button* button,
        int* x, int* y,
        int* w, int* h
);

/**
 *  \brief Hide or unhide a button
 *
 *  \param button button to update
 *  \param hide *1* to hide the button, *1* to show it, -1 to query the
 *  current state
 *
 *  \return 0 on success, -1 on error. If *hide* is -1, then the function
 *  returns whether the button is hidden or not
 */
extern DECLSPEC int SDLCALL SDLU_HideButton(
        SDLU_Button* button,
        int hide
);

/**
 *  \brief Set the title of a button
 *
 *  \note Only applicable to text buttons
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GetTextButtonData()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonText(
        SDLU_Button* button,
        const char* text
);

/**
 *  \brief Set the size of a text button's title
 *
 *  \param button Button to update.
 *  \param size The new text size (in pixels).
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GetTextButtonData()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonTextSize(
        SDLU_Button* button,
        Uint32 size
);

/**
 *  \brief Set custom colors for a button
 *
 *  If the button is an image button, text_color is ignored, fill_color is set
 *  as the color mod of the texture, and box_color is the color of the border of
 *  the button.
 *
 *  \param button Button to update
 *  \param text_color New text color
 *  \param fill_color New fill color [ or color mod ]
 *  \param box_color New box color
 *
 *  \return 0 on success or -1 on error.
 *
 *  \sa SDLU_GetTextButtonData()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonColor(
        SDLU_Button* button,
        SDL_Color text_color,
        SDL_Color fill_color,
        SDL_Color box_color
);

/**
 *  \brief Set the blendmode of the button
 *
 *  \param button Button to update
 *  \param blendmode The new blendmode, see SDL_blendmode.h for possible values
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GetTextButtonData()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonBlendMode(
        SDLU_Button* button,
        SDL_BlendMode blendmode
);

/**
 *  \brief Get the text data of a button.
 *
 *  This function will fill an SDLU_TextButtonData structure with the text data
 *  of the button, which includes its font size, title, colors and blendmode
 *
 *  \param button Button to query
 *  \param data A pointer that will be filled with the button's text data
 *
 *  \return 0 on success or -1 on error.
 *
 *  \sa SDLU_SetButtonText()
 *  \sa SDLU_SetButtonTextSize()
 *  \sa SDLU_SetButtonColor()
 *  \sa SDLU_SetButtonBlendMode()
 */
extern DECLSPEC int SDLCALL SDLU_GetTextButtonData(
        SDLU_Button* button,
        SDLU_TextButtonData* data
);

/**
 *  \brief Set the image of a button
 *
 *  \param button Button to change
 *  \param image The new button image
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GetButtonImage()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonImage(
        SDLU_Button* button,
        SDL_Texture* image
);

/**
 *  \brief Get the image data of a button as a texture.
 *
 *  \note Only applicable to image buttons.
 *
 *  \param button Button to query
 *  \param image Pointer to a texture (SDL_Texture**), will be filled with the
 *  image of the button
 *
 *  \code
 *  // Use like this
 *  SDL_Texture* button_image;
 *  SDLU_GetButtonImage(button, &button_image);
 *  \endcode
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_SetButtonImage()
 */
extern DECLSPEC int SDLCALL SDLU_GetButtonImage(
        SDLU_Button* button,
        SDL_Texture** image
);

/**
 *  \brief Add userdata to a button
 *
 *  \param button button to add the userdata to
 *  \param key key with which the data will be stored/referenced
 *  \param data The data to store, NULL to delete the entry
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GetButtonData()
 *  \sa SDLU_DelButtonData()
 */
extern DECLSPEC int SDLCALL SDLU_AddButtonData(
        SDLU_Button* button,
        const char* key,
        void *data
);

/**
 *  \brief Get previously stored userdata from a button
 *
 *  \param button button to query
 *  \param key the key with which the data was stored
 *
 *  \return the stored userdata on success, -1 on error
 *
 *  \sa SDLU_AddButtonData()
 *  \sa SDLU_DelButtonData()
 */
extern DECLSPEC void* SDLCALL SDLU_GetButtonData(
        SDLU_Button* button,
        const char* key
);

/**
 *  \brief Delete previously stored userdata from a button
 *
 *  \param button button to delete the userdata from
 *  \param key the key with which the data was stored
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_AddButtonData()
 *  \sa SDLU_GetButtonData()
 */
extern DECLSPEC int SDLCALL SDLU_DelButtonData(
        SDLU_Button* button,
        const char* key
);

/**
 *  \brief Set a custom render function for a button.
 *
 *  This function shall be only used when you want to apply some special effects
 *  when rendering a button, such as gradients, light effects, special borders
 *  etc. Otherwise, the built-in render function is just as great.
 *
 *  The function must return *int* (0 on success, -1 on error) and take as its
 *  only argument an SDLU_Button* structure.
 *
 *  If you want to reset the render function of the button, just pass NULL as
 *  the second parameter.
 *
 *  \param button Button to set a custom render function
 *  \param render The new render function, NULL to reset
 *
 *  \return 0 on success, -1 on error.
 *
 *  \sa SDLU_RenderButton()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonRenderFunc(
        SDLU_Button * button,
        int (*render)(SDLU_Button *)
);

/**
 *  \name Callback types
 */
/*@{*/
#define SDLU_PRESS_CALLBACK 0x00
#define SDLU_HOVER_CALLBACK 0x01
/*@}*/

/**
 *  \brief Set a button callback function
 *
 *  \param button Button to be assigned the callback
 *  \param type SDLU_PRESS_CALLBACK or SDLU_HOVER_CALLBACK
 *  \param callback The callback function
 *  \param arg      The argument that will be given to the callback function.
 *
 *  \return 0 on success, -1 on error.
 *
 *  \sa SDLU_Callback
 *  \sa SDLU_DelButtonCallback()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonCallback(
        SDLU_Button* button,
        int type,
        SDLU_Callback callback,
        void* arg
);

/**
 *  \brief Delete a button callback
 *
 *  \param button button to update
 *  \param type SDLU_PRESS_CALLBACK to delete the press callback,
 *  SDLU_HOVER_CALLBACK to delete the hover callback
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_DelButtonCallback(
        SDLU_Button* button,
        int type
);

/**
 *  \brief Set how the button responds when pressed or hovered
 *
 *  \param button button to update
 *  \param type SDLU_PRESS_ACTION or SDLU_HOVER_ACTION
 *  \param action the new action, it can be a mask of the SDLU_PRESS_* or
 *  SDLU_HOVER_* macros OR'd together.
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_HOVER_NONE
 *  \sa SDLU_HOVER_BG
 *  \sa SDLU_HOVER_UL
 *  \sa SDLU_HOVER_FG
 *  \sa SDLU_HOVER_CURSOR
 *  \sa SDLU_PRESS_NONE
 *  \sa SDLU_PRESS_INVERT
 *
 *  \sa SDLU_GetButtonAction()
 */
extern DECLSPEC int SDLCALL SDLU_SetButtonAction(
        SDLU_Button* button,
        int type,
        int action
);

/**
 *  \brief Get the press or hover action of a button
 *
 *  \param button button to query
 *  \param type SDLU_PRESS_ACTION or SDLU_HOVER_ACTION
 *
 *  \return the button action on success, -1 on error
 *
 *  \sa SDLU_SetButtonAction()
 */
extern DECLSPEC int SDLCALL SDLU_GetButtonAction(
        SDLU_Button* button,
        int type
);

/**
 *  \brief Get the current state of the button
 *
 *  \param button button to query
 *
 *  \return SDLU_PRESSED if the button was pressed, SDLU_HOVERED if hovered,
 *  SDLU_IDLE otherwise
 */
extern DECLSPEC int SDLCALL SDLU_GetButtonState(SDLU_Button* button);

/**
 *  \brief Render a button
 */
#define SDLU_RenderButton(button) (button)->render((button))

/**
 *  \brief Destroy a button
 *
 *  After the last button is destroyed, the event watch is also deleted
 *  automatically
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_DestroyButton(SDLU_Button* button);

/* Do not use these */
extern DECLSPEC Uint32 SDLCALL SDLU_GetButtonHoverEvent(void);
extern DECLSPEC Uint32 SDLCALL SDLU_GetButtonPressEvent(void);
extern DECLSPEC Uint32 SDLCALL SDLU_GetButtonReleaseEvent(void);
extern DECLSPEC Uint32 SDLCALL SDLU_GetButtonLostFocusEvent(void);

#ifdef __cplusplus
}
#endif

#include "close_code.h"
#endif /* SDLU_BUTTON_H */


