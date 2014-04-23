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
 *  \brief Create a new combo box
 */
extern DECLSPEC SDLU_ComboBox* SDLCALL SDLU_CreateComboBox(SDL_Window* window);

/**
 *  \brief Set geometry of combo box
 *
 *  \param combobox Combo box to change
 *  \param x, y New position
 *  \param w, h New size
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetComboBoxGeometry(
        SDLU_ComboBox* combobox,
        int x, int y,
        int w, int h
);

/**
 *  \brief Add a new item to a combo box
 *
 *  \param combobox Combo box to add item to
 *  \param item Item to add
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_AddComboBoxItem(
        SDLU_ComboBox** combobox,
        const char* item
);

/**
 *  \brief Remove an item
 *
 *  \param combobox Combo box to remove item from
 *  \param item Item to remove
 *
 *  \return 0 on success, -1 on error
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
 *
 *  The callback function takes two 'void*' arguments, see the docs for
 *  SDLU_Callback. The first argument is a pointer to the combo box, while the
 *  second one is userdata. The callback is executed every time a new item is
 *  chosen from the combo box. A basic callback function should do something
 *  like this:
 *
 *  \code
 *  void callback_function(void* _this, void* userdata)
 *  {
 *      SDLU_ComboBox* this = (SDLU_ComboBox*) this;
 *
 *      // Do something, e.g:
 *      printf("New item: %s\n", this->current);
 *      printf("New item index: %s\n", this->current_index);
 *  }
 *  \endcode
 *
 *  \param combobox Combo box to set the callback for
 *  \param callback The new callback function
 *  \param arg Optional argument that is passed to the callback function
 *
 *  \return 0 on success, -1 on error
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
