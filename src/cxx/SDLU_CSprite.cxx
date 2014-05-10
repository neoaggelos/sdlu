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

SDLU::Sprite::Sprite( )
{
    this->sprite = NULL;
}

SDLU::Sprite::Sprite(SDL_Renderer* renderer, SDL_Texture* data, int num)
{
    this->sprite = SDLU_CreateSprite(renderer, data, num);
}

SDLU::Sprite::Sprite(SDLU::Renderer* renderer, SDL_Texture* data, int num)
{
    this->sprite = SDLU_CreateSprite(renderer->GetRenderer(), data, num);
}

SDLU::Sprite::Sprite(SDL_Renderer* renderer, SDLU::Texture* data, int num)
{
    this->sprite = SDLU_CreateSprite(renderer, data->GetTexture(), num);
}

SDLU::Sprite::Sprite(SDLU::Renderer* renderer, SDLU::Texture* data, int num)
{
    this->sprite = SDLU_CreateSprite(renderer->GetRenderer(), data->GetTexture(), num);
}

SDLU::Sprite::Sprite(SDL_Renderer* renderer, SDL_RWops* rwops, int freesrc, int frames)
{
    this->sprite = SDLU_CreateSpriteFromRW(renderer, rwops, freesrc, frames);
}

SDLU::Sprite::Sprite(SDLU::Renderer* renderer, SDL_RWops* rwops, int freesrc, int frames)
{
    this->sprite = SDLU_CreateSpriteFromRW(renderer->GetRenderer(), rwops, freesrc, frames);
}

SDLU::Sprite::Sprite(SDL_Renderer* renderer, SDLU::RWops* rwops, int freesrc, int frames)
{
    this->sprite = SDLU_CreateSpriteFromRW(renderer, rwops->GetRWops(), freesrc, frames);
}

SDLU::Sprite::Sprite(SDLU::Renderer* renderer, SDLU::RWops* rwops, int freesrc, int frames)
{
    this->sprite = SDLU_CreateSpriteFromRW(renderer->GetRenderer(), rwops->GetRWops(), freesrc, frames);
}

SDLU::Sprite::Sprite(SDL_Renderer* renderer, const char* file, int num)
{
    this->sprite = SDLU_CreateSpriteFromFile( renderer, file, num);
}

SDLU::Sprite::Sprite(SDLU::Renderer* renderer, const char* file, int num)
{
    this->sprite = SDLU_CreateSpriteFromFile( renderer->GetRenderer(), file, num );
}

SDLU::Sprite::Sprite(SDL_Renderer* renderer, std::string file, int num)
{
    this->sprite = SDLU_CreateSpriteFromFile( renderer, file.c_str(), num);
}

SDLU::Sprite::Sprite(SDLU::Renderer* renderer, std::string file, int num)
{
    this->sprite = SDLU_CreateSpriteFromFile( renderer->GetRenderer(), file.c_str(), num );
}

SDLU::Sprite::Sprite(SDLU_Sprite* sprite)
{
    this->sprite = sprite;
}

SDLU::Sprite::~Sprite( )
{
    SDLU_DestroySprite( this->sprite );
}

SDLU_Sprite* SDLU::Sprite::GetSprite( )
{
    return this->sprite;
}

int SDLU::Sprite::SetVelocity( double xvel, double yvel )
{
    return SDLU_SetSpriteVelocity( this->sprite, xvel, yvel );
}

int SDLU::Sprite::SetDirection( double vel, double angle )
{
    return SDLU_SetSpriteDirection( this->sprite, vel, angle );
}

int SDLU::Sprite::GetDirection( double* angle )
{
    return SDLU_GetSpriteDirection( this->sprite, angle );
}

int SDLU::Sprite::GetVelocity( double* xvel, double* yvel )
{
    return SDLU_GetSpriteVelocity(this->sprite, xvel, yvel);
}

int SDLU::Sprite::SetGeometry( int x, int y, int w, int h )
{
    return SDLU_SetSpriteGeometry( this->sprite, x, y, w, h );
}

int SDLU::Sprite::GetGeometry(int *x, int *y, int *w, int *h)
{
    return SDLU_GetSpriteGeometry( this->sprite, x, y, w, h );
}

int SDLU::Sprite::Pause( int pause )
{
    return SDLU_PauseSprite(this->sprite, pause);
}

int SDLU::Sprite::SetAdvance( int advance )
{
    return SDLU_SetSpriteAdvance( this->sprite, advance );
}

int SDLU::Sprite::GetAdvance( int *advance )
{
    return SDLU_GetSpriteAdvance( this->sprite, advance );
}

int SDLU::Sprite::SetRenderFunc( int (*func)(SDLU_Sprite*) )
{
    return SDLU_SetSpriteRenderFunc(this->sprite, func);
}

int SDLU::Sprite::SetMoveFunc( int (*func)(SDLU_Sprite*) )
{
    return SDLU_SetSpriteMoveFunc(this->sprite, func);
}

int SDLU::Sprite::SetUpdateFunc( int (*func)(SDLU_Sprite*) )
{
    return SDLU_SetSpriteUpdateFunc(this->sprite, func);
}

int SDLU::Sprite::SetMap( SDL_Rect* rect, int frames )
{
    return SDLU_SetSpriteMap( this->sprite, rect, frames );
}

int SDLU::Sprite::GetMap( SDL_Rect* rect )
{
    return SDLU_GetSpriteMap( this->sprite, rect );
}

int SDLU::Sprite::DrawRotated( int draw_rotated )
{
    return SDLU_SpriteDrawRotated( this->sprite, draw_rotated );
}

int SDLU::Sprite::AddData(const char* key, void* value)
{
    return SDLU_AddSpriteData(this->sprite, key, value);
}

void* SDLU::Sprite::GetData(const char* key)
{
    return SDLU_GetSpriteData(this->sprite, key);
}

int SDLU::Sprite::DelData(const char* key)
{
    return SDLU_DelSpriteData(this->sprite, key);
}

int SDLU::Sprite::AddData(std::string* key, void* value)
{
    return SDLU_AddSpriteData(this->sprite, key->c_str(), value);
}

void* SDLU::Sprite::GetData(std::string* key)
{
    return SDLU_GetSpriteData(this->sprite, key->c_str());
}

int SDLU::Sprite::DelData(std::string* key)
{
    return SDLU_DelSpriteData(this->sprite, key->c_str());
}

int SDLU::Sprite::SetFrameMode( int mode )
{
    return SDLU_SetSpriteFrameMode( this->sprite, mode );
}

int SDLU::Sprite::GetFrameMode( )
{
    return SDLU_GetSpriteFrameMode( this->sprite );
}

SDL_Rect SDLU::Sprite::GetSourceRect( )
{
    return SDLU_GetSpriteSourceRect( this->sprite );
}

int SDLU::Sprite::Move( )
{
    return SDLU_MoveSprite( this->sprite );
}

int SDLU::Sprite::Update( )
{
    return SDLU_UpdateSprite( this->sprite );
}

int SDLU::Sprite::Render( )
{
    return SDLU_RenderSprite( this->sprite );
}
