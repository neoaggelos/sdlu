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

SDLU::Window::Window( )
{
    this->window = NULL;
}

SDLU::Window::Window( const char* title, int x, int y, int w, int h, Uint32 flags )
{
    this->window = SDL_CreateWindow( title, x, y, w, h, flags );
}

SDLU::Window::Window( std::string title, int x, int y, int w, int h, Uint32 flags )
{
    this->window = SDL_CreateWindow( title.c_str(), x, y, w, h, flags );
}

SDLU::Window::Window( const void* data )
{
    this->window = SDL_CreateWindowFrom( data );
}

SDLU::Window::Window( SDL_Window* win )
{
    this->window = win;
}

SDLU::Window::~Window( )
{
    SDL_DestroyWindow( this->window );
}

SDL_Window* SDLU::Window::GetWindow( )
{
    return this->window;
}

int SDLU::Window::GetDisplayIndex( )
{
    return SDL_GetWindowDisplayIndex( this->window );
}

int SDLU::Window::SetDisplayMode( const SDL_DisplayMode *mode )
{
    return SDL_SetWindowDisplayMode( this->window, mode );
}

int SDLU::Window::GetDisplayMode( SDL_DisplayMode *mode )
{
    return SDL_GetWindowDisplayMode( this->window, mode );
}

Uint32 SDLU::Window::GetPixelFormat( )
{
    return SDL_GetWindowPixelFormat( this->window );
}

int SDLU::Window::GetID( )
{
    return SDL_GetWindowID( this->window );
}

Uint32 SDLU::Window::GetFlags( )
{
    return SDL_GetWindowFlags( this->window );
}

void SDLU::Window::SetTitle( const char* title )
{
    SDL_SetWindowTitle( this->window, title );
}

const char* SDLU::Window::GetTitle( )
{
    return SDL_GetWindowTitle( this->window );
}

void SDLU::Window::SetTitle( std::string title )
{
    SDL_SetWindowTitle( this->window, title.c_str() );
}

void SDLU::Window::SetIcon( SDL_Surface *icon )
{
    SDL_SetWindowIcon( this->window, icon );
}

void SDLU::Window::SetData( const char* name, void* userdata )
{
    SDL_SetWindowData( this->window, name, userdata );
}

void* SDLU::Window::GetData( const char* name )
{
    return SDL_GetWindowData( this->window, name );
}

void SDLU::Window::SetData( std::string name, void* userdata )
{
    SDL_SetWindowData( this->window, name.c_str(), userdata );
}

void* SDLU::Window::GetData( std::string name )
{
    return SDL_GetWindowData( this->window, name.c_str() );
}

void SDLU::Window::SetPosition( int x, int y )
{
    SDL_SetWindowPosition( this->window, x, y );
}

void SDLU::Window::GetPosition( int *x, int *y )
{
    SDL_GetWindowPosition( this->window, x, y );
}

void SDLU::Window::SetSize( int w, int h )
{
    SDL_SetWindowSize( this->window, w, h );
}

void SDLU::Window::GetSize( int *w, int *h )
{
    SDL_GetWindowSize( this->window, w, h );
}

void SDLU::Window::SetMinimumSize( int w, int h )
{
    SDL_SetWindowMinimumSize( this->window, w, h );
}

void SDLU::Window::GetMinimumSize( int *w, int *h )
{
    SDL_GetWindowMinimumSize( this->window, w, h );
}

void SDLU::Window::SetMaximumSize( int w, int h )
{
    SDL_SetWindowMaximumSize( this->window, w, h );
}

void SDLU::Window::GetMaximumSize( int *w, int *h )
{
    SDL_GetWindowMaximumSize( this->window, w, h );
}

void SDLU::Window::SetBordered( SDL_bool bordered )
{
    SDL_SetWindowBordered( this->window, bordered );
}

void SDLU::Window::Show( )
{
    SDL_ShowWindow( this->window );
}

void SDLU::Window::Hide( )
{
    SDL_HideWindow( this->window );
}

void SDLU::Window::Raise( )
{
    SDL_RaiseWindow( this->window );
}

void SDLU::Window::Maximize( )
{
    SDL_MaximizeWindow( this->window );
}

void SDLU::Window::Minimize( )
{
    SDL_MinimizeWindow( this->window );
}

void SDLU::Window::Restore( )
{
   SDL_RestoreWindow( this->window );
}

SDL_Surface* SDLU::Window::GetSurface( )
{
    return SDL_GetWindowSurface( this->window );
}

int SDLU::Window::UpdateSurface( )
{
    return SDL_UpdateWindowSurface( this->window );
}

int SDLU::Window::UpdateSurfaceRects( const SDL_Rect *rects, int n )
{
    return SDL_UpdateWindowSurfaceRects( this->window, rects, n );
}

void SDLU::Window::SetGrab( SDL_bool grabbed )
{
    return SDL_SetWindowGrab( this->window, grabbed );
}

SDL_bool SDLU::Window::GetGrab( )
{
    return SDL_GetWindowGrab( this->window );
}

int SDLU::Window::SetBrightness( float brightness )
{
    return SDL_SetWindowBrightness( this->window, brightness );
}

float SDLU::Window::GetBrightness( )
{
    return SDL_GetWindowBrightness( this->window );
}

int SDLU::Window::SetGammaRamp( Uint16* r, Uint16* g, Uint16* b)
{
    return SDL_SetWindowGammaRamp( this->window, r, g, b );
}

int SDLU::Window::GetGammaRamp( Uint16* r, Uint16* g, Uint16* b)
{
    return SDL_GetWindowGammaRamp( this->window, r, g, b );
}

SDL_Renderer* SDLU::Window::GetRenderer( )
{
    return SDL_GetRenderer( this->window );
}

SDL_GLContext SDLU::Window::CreateContext( )
{
    return SDL_GL_CreateContext( this->window );
}

int SDLU::Window::MakeCurrent( SDL_GLContext context )
{
    return SDL_GL_MakeCurrent( this->window, context );
}

void SDLU::Window::Swap( )
{
    return SDL_GL_SwapWindow( this->window );
}

Uint32 SDLU::Window::MapRGBA( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    return SDLU_WinMapRGBA( this->window, r, g, b, a );
}

Uint32 SDLU::Window::MapRGB( Uint8 r, Uint8 g, Uint8 b )
{
    return this->MapRGBA(r,g,b,SDL_ALPHA_OPAQUE);
}

