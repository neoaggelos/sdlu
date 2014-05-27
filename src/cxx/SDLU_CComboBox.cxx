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

#include "SDLU.h"
#include "SDLU_common.h"

SDLU::ComboBox::ComboBox()
{
    this->combobox = NULL;
}

SDLU::ComboBox::ComboBox(SDL_Window* window)
{
    this->combobox = SDLU_CreateComboBox(window);
}

SDLU::ComboBox::ComboBox(SDLU::Window* window)
{
    this->combobox = SDLU_CreateComboBox(window->GetWindow());
}

SDLU::ComboBox::ComboBox(SDLU_ComboBox* cb)
{
    this->combobox = cb;
}

SDLU::ComboBox::~ComboBox()
{
    SDLU_DestroyComboBox(this->combobox);
}

SDLU_ComboBox* SDLU::ComboBox::GetComboBox()
{
    return this->combobox;
}

int SDLU::ComboBox::SetGeometry(int x, int y, int w, int h)
{
    return SDLU_SetComboBoxGeometry(this->combobox, x, y, w, h);
}

int SDLU::ComboBox::SetCallback(SDLU_Callback callback, void* arg)
{
    return SDLU_SetComboBoxCallback(this->combobox, callback, arg);
}

int SDLU::ComboBox::SetStyles(SDLU_Styles* styles)
{
    return SDLU_SetComboBoxStyles(this->combobox, styles);
}

int SDLU::ComboBox::GetStyles(SDLU_Styles* styles)
{
    return SDLU_GetComboBoxStyles(this->combobox, styles);
}

int SDLU::ComboBox::Render()
{
    return SDLU_RenderComboBox(this->combobox);
}

int SDLU::ComboBox::AddItem(const char* item)
{
    return SDLU_AddComboBoxItem(&(this->combobox), item);
}

int SDLU::ComboBox::DelItem(const char* item)
{
    return SDLU_DelComboBoxItem(&(this->combobox), item);
}

int SDLU::ComboBox::AddItem(std::string item)
{
    return SDLU_AddComboBoxItem(&(this->combobox), item.c_str());
}

int SDLU::ComboBox::DelItem(std::string item)
{
    return SDLU_DelComboBoxItem(&(this->combobox), item.c_str());
}

