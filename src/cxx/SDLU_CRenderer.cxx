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

#include "SDL_ttf.h"

SDLU::Renderer::Renderer( )
{
    this->renderer = NULL;
}

SDLU::Renderer::Renderer( SDL_Window* window, int driver, Uint32 flags )
{
    this->renderer = SDL_CreateRenderer( window, driver, flags );
}

SDLU::Renderer::Renderer( SDL_Window* window, Uint32 flags )
{
    this->renderer = SDL_CreateRenderer( window, -1, flags );
}

SDLU::Renderer::Renderer( SDLU::Window* window, int driver, Uint32 flags )
{
    this->renderer = SDL_CreateRenderer( window->GetWindow(), driver, flags );
}

SDLU::Renderer::Renderer( SDLU::Window* window, Uint32 flags )
{
    this->renderer = SDL_CreateRenderer( window->GetWindow(), -1, flags );
}

SDLU::Renderer::Renderer( SDL_Renderer* renderer )
{
    this->renderer = renderer;
}

SDLU::Renderer::Renderer( SDL_Surface* surface )
{
    this->renderer = SDL_CreateSoftwareRenderer( surface );
}

SDLU::Renderer::~Renderer( )
{
    SDL_DestroyRenderer( this->renderer );
}

SDL_Renderer* SDLU::Renderer::GetRenderer( )
{
    return this->renderer;
}

SDL_Window* SDLU::Renderer::GetWindow( )
{
    return SDLU_GetWindow( this->renderer );
}

int SDLU::Renderer::GetInfo( SDL_RendererInfo* info )
{
    return SDL_GetRendererInfo( this->renderer, info );
}

int SDLU::Renderer::GetOutputSize( int *w, int *h )
{
    return SDL_GetRendererOutputSize( this->renderer, w, h );
}

SDL_bool SDLU::Renderer::RenderTargetSupported( )
{
    return SDL_RenderTargetSupported( this->renderer );
}

int SDLU::Renderer::SetRenderTarget( SDL_Texture* texture )
{
    return SDL_SetRenderTarget( this->renderer, texture );
}

int SDLU::Renderer::SetRenderTarget( SDLU::Texture* texture )
{
    return SDL_SetRenderTarget( this->renderer, texture->GetTexture() );
}

SDL_Texture* SDLU::Renderer::GetRenderTarget( )
{
    return SDL_GetRenderTarget( this->renderer );
}

int SDLU::Renderer::SetLogicalSize( int w, int h )
{
    return SDL_RenderSetLogicalSize( this->renderer, w, h );
}

void SDLU::Renderer::GetLogicalSize( int *w, int *h )
{
    SDL_RenderGetLogicalSize( this->renderer, w, h );
}

int SDLU::Renderer::SetViewport( const SDL_Rect * rect )
{
    return SDL_RenderSetViewport( this->renderer, rect );
}

void SDLU::Renderer::GetViewport( SDL_Rect * rect )
{
    SDL_RenderGetViewport( this->renderer, rect );
}

int SDLU::Renderer::SetClipRect( const SDL_Rect * rect )
{
    return SDL_RenderSetClipRect( this->renderer, rect );
}

void SDLU::Renderer::GetClipRect( SDL_Rect * rect )
{
    SDL_RenderGetClipRect( this->renderer, rect );
}

int SDLU::Renderer::SetScale( float x, float y )
{
    return SDL_RenderSetScale( this->renderer, x, y );
}

void SDLU::Renderer::GetScale( float *x, float *y )
{
    SDL_RenderGetScale( this->renderer, x, y );
}

int SDLU::Renderer::SetDrawColor( Uint8 r, Uint8 g, Uint8 b,
                                  Uint8 a = SDL_ALPHA_OPAQUE )
{
    return SDL_SetRenderDrawColor( this->renderer, r, g, b, a );
}

int SDLU::Renderer::SetDrawColor( SDL_Color c )
{
    return SDL_SetRenderDrawColor( this->renderer, c.r, c.g, c.b, c.a );
}

int SDLU::Renderer::GetDrawColor( Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a )
{
    return SDL_GetRenderDrawColor( this->renderer, r, g, b, a );
}

int SDLU::Renderer::GetDrawColor( SDL_Color *c )
{
    return SDL_SetRenderDrawColor( this->renderer, c->r, c->g, c->b, c->a );
}

int SDLU::Renderer::SetBlendMode( SDL_BlendMode blendmode )
{
    return SDL_SetRenderDrawBlendMode( this->renderer, blendmode );
}

int SDLU::Renderer::GetBlendMode( SDL_BlendMode * blendmode )
{
    return SDL_GetRenderDrawBlendMode( this->renderer, blendmode );
}

int SDLU::Renderer::Clear( )
{
    return SDL_RenderClear( this->renderer );
}

int SDLU::Renderer::DrawPoint( int x, int y )
{
    return SDL_RenderDrawPoint( this->renderer, x, y );
}

int SDLU::Renderer::DrawPoints( const SDL_Point * points, int n )
{
    return SDL_RenderDrawPoints( this->renderer, points, n );
}

int SDLU::Renderer::DrawLine( int x1, int y1, int x2, int y2 )
{
    return SDL_RenderDrawLine( this->renderer, x1, y1, x2, y2 );
}

int SDLU::Renderer::DrawLines( const SDL_Point * points, int n )
{
    return SDL_RenderDrawLines( this->renderer, points, n );
}

int SDLU::Renderer::DrawRect( const SDL_Rect * rect )
{
    return SDL_RenderDrawRect( this->renderer, rect );
}

int SDLU::Renderer::DrawRects( const SDL_Rect * rects, int n )
{
    return SDL_RenderDrawRects( this->renderer, rects, n );
}

int SDLU::Renderer::FillRect( const SDL_Rect * rect )
{
    return SDL_RenderFillRect( this->renderer, rect );
}

int SDLU::Renderer::FillRects( const SDL_Rect * rects, int n )
{
    return SDL_RenderFillRects( this->renderer, rects, n );
}

int SDLU::Renderer::Copy( SDL_Texture* texture, const SDL_Rect * srcrect, const SDL_Rect * dstrect  )
{
    return SDL_RenderCopy( this->renderer, texture, srcrect, dstrect );
}

int SDLU::Renderer::Copy( SDLU::Texture* texture, const SDL_Rect * srcrect, const SDL_Rect * dstrect  )
{
    return SDL_RenderCopy( this->renderer, texture->GetTexture(), srcrect, dstrect );
}

int SDLU::Renderer::CopyEx( SDL_Texture* texture, const SDL_Rect * srcrect, const SDL_Rect * destrect, const double angle, const SDL_Point * center, const SDL_RendererFlip flip )
{
    return SDL_RenderCopyEx(this->renderer, texture, srcrect, destrect, angle, center, flip );
}

int SDLU::Renderer::CopyEx( SDLU::Texture* texture, const SDL_Rect * srcrect, const SDL_Rect * destrect, const double angle, const SDL_Point * center, const SDL_RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture->GetTexture(), srcrect, destrect, angle, center, flip );
}

int SDLU::Renderer::ReadPixels( const SDL_Rect * rect, Uint32 format,
                                void * pixels, int pitch              )
{
    return SDL_RenderReadPixels( this->renderer, rect, format, pixels, pitch );
}

void SDLU::Renderer::Present( )
{
    return SDL_RenderPresent( this->renderer );
}

Uint32 SDLU::Renderer::MapRGBA( Uint8 r, Uint8 g, Uint8 b,
                                Uint8 a = SDL_ALPHA_OPAQUE )
{
    return SDLU_RenderMapRGBA( this->renderer, r, g, b, a );
}

Uint32 SDLU::Renderer::MapRGB( Uint8 r, Uint8 g, Uint8 b )
{
    return SDLU_RenderMapRGB( this->renderer, r, g, b );
}

int SDLU::Renderer::RenderText( int x, int y, const char* format, ... )
{
    va_list arg;
    va_start( arg, format );
    int ret = SDLU_RenderTextVa( this->renderer, x, y, format, arg );
    va_end(arg);
    return ret;
}

int SDLU::Renderer::RenderTextVa( int x, int y, const char* format, va_list arg )
{
    return SDLU_RenderTextVa( this->renderer, x, y, format, arg );
}

int SDLU::Renderer::RenderText( int x, int y, std::string format, ... )
{
    va_list arg;
    va_start( arg, format );
    int ret = SDLU_RenderTextVa( this->renderer, x, y, format.c_str(), arg );
    va_end(arg);
    return ret;
}

int SDLU::Renderer::RenderTextVa( int x, int y, std::string format, va_list arg )
{
    return SDLU_RenderTextVa( this->renderer, x, y, format.c_str(), arg );
}

void SDLU::Renderer::SetFontSize( Uint32 size )
{
    SDLU_SetFontSize( size );
}

int SDLU::Renderer::GetFontSize( )
{
    return SDLU_GetFontSize( );
}

int SDLU::Renderer::SetTruetypeFont(TTF_Font* font)
{
    return SDLU_SetTruetypeFont(font);
}

int SDLU::Renderer::SetTruetypeFontFile(const char* font, int size)
{
    return SDLU_SetTruetypeFontFile(font, size);
}

int SDLU::Renderer::SetTruetypeFontFile(std::string font, int size)
{
    return SDLU_SetTruetypeFontFile(font.c_str(), size);
}

TTF_Font* SDLU::Renderer::GetTruetypeFont()
{
    return SDLU_GetTruetypeFont();
}

SDL_Texture* SDLU::Renderer::LoadTexture( const char* fname )
{
    return SDLU_LoadTexture( this->renderer, fname );
}

SDL_Texture* SDLU::Renderer::LoadTextureWithColorkey( const char* fname, SDL_Color colorkey)
{
    return SDLU_LoadTextureWithColorkey( this->renderer, fname, colorkey );
}

SDL_Texture* SDLU::Renderer::LoadTexture( std::string fname )
{
    return SDLU_LoadTexture( this->renderer, fname.c_str() );
}

SDL_Texture* SDLU::Renderer::LoadTextureWithColorkey( std::string fname, SDL_Color colorkey)
{
    return SDLU_LoadTextureWithColorkey( this->renderer, fname.c_str(), colorkey );
}

int SDLU::Renderer::CopyTexture( SDL_Texture* texture, int x, int y )
{
    return SDLU_CopyTexture( this->renderer, texture, x, y );
}

int SDLU::Renderer::CopyTexture( SDLU::Texture* texture, int x, int y )
{
    return SDLU_CopyTexture( this->renderer, texture->GetTexture(), x, y );
}

int SDLU::Renderer::DrawCircle( int cx, int cy, int r )
{
    return SDLU_RenderDrawCircle( this->renderer, cx, cy, r );
}

int SDLU::Renderer::DrawOutlineRect( SDL_Rect rect,
                                     SDL_Color outline, SDL_Color fill )
{
    return SDLU_RenderDrawOutlineRect( this->renderer, rect, outline, fill );
}

void SDLU::Renderer::Begin( int mode )
{
    SDLU_RenderBegin( mode );
}

void SDLU::Renderer::SetPoint( int x, int y )
{
    SDLU_RenderSetPoint( x, y );
}

void SDLU::Renderer::SetPoints( SDL_Point* points, int num_points )
{
    SDLU_RenderSetPoints(points, num_points);
}

int SDLU::Renderer::End( )
{
    return SDLU_RenderEnd( this->renderer );
}

int SDLU::Renderer::FillPolygon( SDL_Point* points, int n )
{
    return SDLU_RenderFillPolygon( this->renderer, points, n );
}

int SDLU::Renderer::DrawPolygon( SDL_Point* points, int n )
{
    return SDLU_RenderDrawPolygon( this->renderer, points, n );
}

int SDLU::Renderer::MultiCopy( SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest, int n, const char* format )
{
    return SDLU_RenderMultiCopy( this->renderer, texture, src, dest, n, format );
}

int SDLU::Renderer::MultiCopy( SDLU::Texture* texture, SDL_Rect* src, SDL_Rect* dest, int n, const char* format )
{
    return SDLU_RenderMultiCopy( this->renderer, texture->GetTexture(), src, dest, n, format );
}

int SDLU::Renderer::MultiCopy( SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest, int n, std::string format )
{
    return SDLU_RenderMultiCopy( this->renderer, texture, src, dest, n, format.c_str() );
}

int SDLU::Renderer::MultiCopy( SDLU::Texture* texture, SDL_Rect* src, SDL_Rect* dest, int n, std::string format )
{
    return SDLU_RenderMultiCopy( this->renderer, texture->GetTexture(), src, dest, n, format.c_str() );
}

int SDLU::Renderer::GL_CacheState( void )
{
    return SDLU_GL_RenderCacheState( this->renderer );
}

int SDLU::Renderer::GL_RestoreState( void )
{
    return SDLU_GL_RenderRestoreState( this->renderer );
}

