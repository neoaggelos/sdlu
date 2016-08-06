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

#include "SDLU.h"
#include "SDLU_common.h"

SDLU::Button::Button( )
{
    this->button = NULL;
}

SDLU::Button::Button( SDL_Window * window, const char* text, Uint32 flags)
{
    this->button = SDLU_CreateButton( window, text, flags );
}

SDLU::Button::Button( SDL_Window * window, std::string text, Uint32 flags)
{
    this->button = SDLU_CreateButton( window, text.c_str(), flags );
}

SDLU::Button::Button( SDLU::Window * window, const char* text, Uint32 flags )
{
    this->button = SDLU_CreateButton( window->GetWindow(), text, flags );
}

SDLU::Button::Button( SDLU::Window* window, std::string text, Uint32 flags )
{
    this->button = SDLU_CreateButton( window->GetWindow(), text.c_str(), flags );
}

SDLU::Button::Button( SDL_Window* window, SDL_Texture* image, Uint32 flags )
{
    this->button = SDLU_CreateButton( window, image, flags );
}

SDLU::Button::Button( SDLU::Window* window, SDL_Texture *image, Uint32 flags )
{
    this->button = SDLU_CreateButton( window->GetWindow(), image, flags );
}

SDLU::Button::Button(SDL_Window* window, SDLU::Texture* image, Uint32 flags )
{
    this->button = SDLU_CreateButton(window, image->GetTexture(), flags);
}

SDLU::Button::Button(SDLU::Window* window, SDLU::Texture* image, Uint32 flags)
{
    this->button = SDLU_CreateButton(window->GetWindow(), image->GetTexture(), flags);
}

SDLU::Button::Button( SDLU_Button* button )
{
    this->button = button;
}

SDLU::Button::~Button( )
{
    SDLU_DestroyButton( this->button );
}

SDLU_Button* SDLU::Button::GetButton( )
{
    return this->button;
}

Uint32 SDLU::Button::GetFlags()
{
    return SDLU_GetButtonFlags(this->button);
}

int SDLU::Button::SetGeometry( int x, int y, int w, int h )
{
    return SDLU_SetButtonGeometry( this->button, x, y, w, h );
}

int SDLU::Button::SetStyles( SDLU_Styles* styles )
{
    return SDLU_SetButtonStyles( this->button, styles );
}

int SDLU::Button::GetStyles( SDLU_Styles* styles )
{
    return SDLU_GetButtonStyles( this->button, styles );
}

int SDLU::Button::SetImage( SDL_Texture* image )
{
    return SDLU_SetButtonImage( this->button, image );
}

int SDLU::Button::SetImage(SDLU::Texture* image)
{
    return SDLU_SetButtonImage(this->button, image->GetTexture());
}

int SDLU::Button::Hide( int hide )
{
    return SDLU_HideButton( this->button, hide );
}

int SDLU::Button::SetAction( int type, int action )
{
    return SDLU_SetButtonAction( this->button, type, action );
}

int SDLU::Button::GetAction( int type )
{
    return SDLU_GetButtonAction( this->button, type );
}

int SDLU::Button::SetCallback(int type, SDLU_Callback callback, void* arg)
{
    return SDLU_SetButtonCallback(this->button, type, callback, arg);
}

int SDLU::Button::DelCallback( int type )
{
    return SDLU_DelButtonCallback( this->button, type );
}

int SDLU::Button::SetHotkey( SDL_Scancode hotkey )
{
    return SDLU_SetButtonHotkey( this->button, hotkey );
}

int SDLU::Button::GetImage( SDL_Texture** image )
{
    return SDLU_GetButtonImage( this->button, image );
}

int SDLU::Button::GetImage( SDLU::Texture** image )
{
    SDL_Texture* tex;
    int result = 0;

    result |= SDLU_GetButtonImage(this->button, &tex);
    *image = new SDLU::Texture(tex);

    return result;
}

int SDLU::Button::AddData(const char* key, void* value)
{
    return SDLU_AddButtonData(this->button, key, value);
}

void* SDLU::Button::GetData(const char* key)
{
    return SDLU_GetButtonData(this->button, key);
}

int SDLU::Button::DelData(const char* key)
{
    return SDLU_DelButtonData(this->button, key);
}

int SDLU::Button::AddData(std::string* key, void* value)
{
    return SDLU_AddButtonData(this->button, key->c_str(), value);
}

void* SDLU::Button::GetData(std::string* key)
{
    return SDLU_GetButtonData(this->button, key->c_str());
}

int SDLU::Button::DelData(std::string* key)
{
    return SDLU_DelButtonData(this->button, key->c_str());
}

int SDLU::Button::GetGeometry(int *x, int *y, int *w, int *h)
{
    return SDLU_GetButtonGeometry(this->button, x, y, w, h);
}

int SDLU::Button::Render( )
{
    return SDLU_RenderButton( this->button );
}

int SDLU::Button::GetState()
{
    return SDLU_GetButtonState( this->button );
}

