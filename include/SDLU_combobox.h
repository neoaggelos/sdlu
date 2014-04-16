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
 *  \file SDLU_combobox.h
 *
 *  \brief The SDLU_ComboBox API
 */

#ifndef SDLU_COMBOBOX_H
#define SDLU_COMBOBOX_H

#include "SDL.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief The ComboBox structure
 */
typedef struct {
    Uint32 id;              /**< unique identifier -- READ ONLY **/
    const char* name;       /**< user-defined name **/

    SDL_Window* window;     /**< parent window **/
    SDL_Rect rect;          /**< position **/
    int open;               /**< whether the combobox is open **/

    int num_items;          /**< counter of items **/
    void *data;             /**< combo box items data **/

    SDLU_Callback callback; /**< callback function **/
    void* arg;              /**< callback argument **/

    int current_index;      /**< index to the current item **/
    const char* current;    /**< current item **/
    void *current_item;     /**< this is used internally **/
} SDLU_ComboBox;

/**
 *  \brief Create a new emtpy combo box
 */
extern DECLSPEC SDLU_ComboBox* SDLCALL SDLU_CreateComboBox(SDL_Window* window);

/**
 *  \brief Set geometry
 */
extern DECLSPEC int SDLCALL SDLU_SetComboBoxGeometry(
        SDLU_ComboBox* combobox,
        int x, int y,
        int w, int h
);

/**
 *  \brief Add a new item
 */
extern DECLSPEC int SDLCALL SDLU_AddComboBoxItem(
        SDLU_ComboBox** combobox,
        const char* item
);

/**
 *  \brief Remove an item
 */
extern DECLSPEC int SDLCALL SDLU_DelComboBoxItem(
        SDLU_ComboBox** combobox,
        const char* item
);

/**
 *  \brief Render combo box
 */
extern DECLSPEC int SDLCALL SDLU_RenderComboBox(SDLU_ComboBox* combobox);

/**
 *  \brief Set combo box callback
 */
extern DECLSPEC int SDLCALL SDLU_SetComboBoxCallback(
        SDLU_ComboBox* combobox,
        SDLU_Callback callback,
        void *arg
);

/**
 *  \brief Destroy combo box
 */
extern DECLSPEC int SDLCALL SDLU_DestroyComboBox(SDLU_ComboBox* combobox);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_COMBOBOX_H */
