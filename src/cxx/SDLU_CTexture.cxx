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

SDLU::Texture::Texture( )
{
    this->texture = NULL;
}

SDLU::Texture::Texture(SDL_Renderer* renderer, Uint32 format, int access, int w, int h)
{
    this->texture = SDL_CreateTexture(renderer, format, access, w, h);
}

SDLU::Texture::Texture(SDLU::Renderer* renderer, Uint32 format, int access, int w, int h)
{
    this->texture = SDL_CreateTexture(renderer->GetRenderer(), format, access, w, h);
}

SDLU::Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surface)
{
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
}

SDLU::Texture::Texture(SDLU::Renderer* renderer, SDL_Surface* surface)
{
    this->texture = SDL_CreateTextureFromSurface(renderer->GetRenderer(), surface);
}

SDLU::Texture::Texture(SDL_Renderer* renderer, const char* file)
{
    this->texture = SDLU_LoadTexture(renderer, file);
}

SDLU::Texture::Texture(SDLU::Renderer* renderer, const char* file)
{
    this->texture = SDLU_LoadTexture(renderer->GetRenderer(), file);
}

SDLU::Texture::Texture(SDL_Renderer* renderer, std::string file)
{
    this->texture = SDLU_LoadTexture(renderer, file.c_str());
}

SDLU::Texture::Texture(SDLU::Renderer* renderer, std::string file)
{
    this->texture = SDLU_LoadTexture(renderer->GetRenderer(), file.c_str());
}

SDLU::Texture::Texture(SDL_Renderer* renderer, const char* file, SDL_Color color)
{
    this->texture = SDLU_LoadTextureWithColorkey(renderer, file, color);
}

SDLU::Texture::Texture(SDLU::Renderer* renderer, const char* file, SDL_Color color)
{
    this->texture = SDLU_LoadTextureWithColorkey(renderer->GetRenderer(), file, color);
}

SDLU::Texture::Texture(SDL_Renderer* renderer, std::string file, SDL_Color color)
{
    this->texture = SDLU_LoadTextureWithColorkey(renderer, file.c_str(), color);
}

SDLU::Texture::Texture(SDLU::Renderer* renderer, std::string file, SDL_Color color)
{
    this->texture = SDLU_LoadTextureWithColorkey(renderer->GetRenderer(), file.c_str(), color);
}

SDLU::Texture::Texture(SDL_Texture* texture)
{
    this->texture = texture;
}

SDLU::Texture::~Texture()
{
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* SDLU::Texture::GetTexture()
{
    return this->texture;
}

int SDLU::Texture::Query(Uint32* format, int* access, int *w, int *h)
{
    return SDL_QueryTexture(this->texture, format, access, w, h);
}

int SDLU::Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_SetTextureColorMod(this->texture, r, g, b);
}

int SDLU::Texture::GetColorMod(Uint8* r, Uint8* g, Uint8* b)
{
    return SDL_GetTextureColorMod(this->texture, r, g, b);
}

int SDLU::Texture::SetAlphaMod(Uint8 a)
{
    return SDL_SetTextureAlphaMod(this->texture, a);
}

int SDLU::Texture::GetAlphaMod(Uint8* a)
{
    return SDL_GetTextureAlphaMod(this->texture, a);
}

int SDLU::Texture::SetBlendMode(SDL_BlendMode blendmode)
{
    return SDL_SetTextureBlendMode(this->texture, blendmode);
}

int SDLU::Texture::GetBlendMode(SDL_BlendMode* blendmode)
{
    return SDL_GetTextureBlendMode(this->texture, blendmode);
}

int SDLU::Texture::Update(const SDL_Rect* rect, const void* pixels, int pitch)
{
    return SDL_UpdateTexture(this->texture, rect, pixels, pitch);
}

int SDLU::Texture::Lock(const SDL_Rect* rect, void** pixels, int* pitch)
{
    return SDL_LockTexture(this->texture, rect, pixels, pitch);
}

void SDLU::Texture::Unlock()
{
    return SDL_UnlockTexture(this->texture);
}

int SDLU::Texture::GL_Bind(float* texw, float* texh)
{
    return SDL_GL_BindTexture(this->texture, texw, texh);
}

int SDLU::Texture::GL_Unbind()
{
    return SDL_GL_UnbindTexture(this->texture);
}

int SDLU::Texture::GetSize(int* w, int* h)
{
    return SDLU_GetTextureSize(this->texture, w, h);
}


