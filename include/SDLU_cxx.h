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
 *  \file SDLU_cxx.h
 *
 *  \brief Defines the cxx classes
 */

#ifndef SDLU_CXX_H
#define SDLU_CXX_H

#include "SDL.h"
#include "SDLU_defs.h"
#include "SDLU_config.h"
#include "begin_code.h"

#if defined( SDLU_CXX ) && defined( __cplusplus )

#include <iostream>

#include "SDL_ttf.h"

/* Organise all classes into the namespace SDLU */
namespace SDLU {

    /* forward-reference all classes */
    class Button;
    class Window;
    class Renderer;
    class Sprite;
    class Texture;
    class IniHandler;
    class RWops;
    class Turtle;

    /**
     *  \brief Wrapper class for the SDL_Window structure
     */
    class DECLSPEC Window {
        private:
            /** We keep the original structure internally. **/
            SDL_Window* window;

        public:

            /** Empty constructor - do not use. **/
            Window( );

            /** SDL_CreateWindow(). **/
            Window( const char* title, int x, int y, int w, int h, Uint32 flags);
            Window( std::string title, int x, int y, int w, int h, Uint32 flags);

            /** SDL_CreateWindowFrom(). **/
            Window( const void *data );

            /** Create from existing SDL_Window. **/
            Window( SDL_Window* win );

            /** Destructor. **/
            ~Window( );

            /** Returns the original window. **/
            SDL_Window* GetWindow( );

            /**
             *  \name SDL2 Functions
             *
             *  \brief The following functions are identical to the functions
             *  provided by SDL2 to work with SDL_Window.
             *
             *  Refer to the SDL2 documentation to see what each one does.
             */
            /*@{*/
            int GetDisplayIndex( );
            int SetDisplayMode( const SDL_DisplayMode *mode );
            int GetDisplayMode( SDL_DisplayMode *mode );
            Uint32 GetPixelFormat( );
            int GetID( );
            Uint32 GetFlags( );
            void SetTitle( const char* title );
            const char* GetTitle( );
            void SetTitle( std::string title );
            void SetIcon( SDL_Surface* icon );
            void SetData( const char* name, void* userdata );
            void* GetData( const char* name );
            void SetData( std::string name, void* userdata );
            void* GetData( std::string name );
            void SetPosition( int x, int y );
            void GetPosition( int *x, int *y );
            void SetSize( int w, int h );
            void GetSize( int *w, int *h );
            void SetMinimumSize( int w, int h );
            void GetMinimumSize( int *w, int *h );
            void SetMaximumSize( int w, int h );
            void GetMaximumSize( int *w, int *h );
            void SetBordered( SDL_bool bordered );
            void Show( );
            void Hide( );
            void Raise( );
            void Maximize( );
            void Minimize( );
            void Restore( );
            SDL_Surface* GetSurface( );
            int UpdateSurface( );
            int UpdateSurfaceRects( const SDL_Rect *rects, int n );
            void SetGrab( SDL_bool grabbed );
            SDL_bool GetGrab( );
            int SetBrightness( float brightness );
            float GetBrightness( );
            int SetGammaRamp(Uint16 *r, Uint16* g, Uint16* b);
            int GetGammaRamp(Uint16 *r, Uint16* g, Uint16* b);
            SDL_Renderer* GetRenderer( );
            SDL_GLContext CreateContext( );
            int MakeCurrent( SDL_GLContext context );
            void Swap( );
            /*@}*/

            /**
             *  \name SDLU Functions
             *
             *  \sa SDLU_WinMapRGBA()
             *  \sa SDLU_WinMapRGB()
             */
            /*@{*/
            Uint32 MapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
            Uint32 MapRGB(Uint8 r, Uint8 g, Uint8 b);
            /*@}*/

    };

    /**
     *  \brief Wrapper class for the SDL_Renderer structure
     */
    class DECLSPEC Renderer {
        private:
            SDL_Renderer* renderer; /**< The original renderer. **/
        public:

            /** Empty constructor - do not use. **/
            Renderer( );

            /** SDL_CreateRenderer(). **/
            Renderer( SDL_Window* window, int driver, Uint32 flags );
            /** SDL_CreateRenderer(). From Window **/
            Renderer( SDLU::Window* window, int driver, Uint32 flags );
            /** SDL_CreateRenderer(), but with driver = -1. **/
            Renderer( SDL_Window* window, Uint32 flags );
            /** SDL_CreateRenderer(), but with driver = -1. **/
            Renderer( SDLU::Window* window, Uint32 flags );

            /** From original structure. **/
            Renderer( SDL_Renderer* renderer );

            /** SDL_CreateSoftwareRenderer(). **/
            Renderer( SDL_Surface* surface );

            /** Destructor. **/
            ~Renderer( );

            /** Get the original renderer. **/
            SDL_Renderer* GetRenderer( );

            /**
             *  \name SDL2 Functions
             *
             *  \brief The following functions are identical to the functions
             *  provided by SDL2 to work with SDL_Renderer.
             *
             *  Refer to the SDL2 documentation to see what each one does.
             */
            /*@{*/
            int GetInfo( SDL_RendererInfo* info );
            int GetOutputSize( int *w, int *h );
            SDL_bool RenderTargetSupported( );
            int SetRenderTarget( SDL_Texture* texture );
            int SetRenderTarget( SDLU::Texture* texture );
            SDL_Texture* GetRenderTarget( );
            int SetLogicalSize( int w, int h );
            void GetLogicalSize( int *w, int *h );
            int SetViewport( const SDL_Rect * rect );
            void GetViewport( SDL_Rect *rect );
            int SetClipRect( const SDL_Rect * rect );
            void GetClipRect( SDL_Rect *rect );
            int SetScale( float x, float y );
            void GetScale( float *x, float *y );
            int SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
            int SetDrawColor( SDL_Color c );
            int GetDrawColor( Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a );
            int GetDrawColor( SDL_Color *c );
            int SetBlendMode( SDL_BlendMode blendmode );
            int GetBlendMode( SDL_BlendMode * blendmode );
            int Clear( );
            int DrawPoint ( int x, int y );
            int DrawPoints( const SDL_Point* points, int n );
            int DrawLine  ( int x1, int y1, int x2, int y2 );
            int DrawLines ( const SDL_Point* points, int n );
            int DrawRect  ( const SDL_Rect * rect );
            int DrawRects ( const SDL_Rect * rects, int n );
            int FillRect  ( const SDL_Rect * rect );
            int FillRects ( const SDL_Rect * rects, int n );
            int Copy( SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect );
            int Copy( SDLU::Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect );
            int CopyEx( SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip );
            int CopyEx( SDLU::Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip );
            int ReadPixels( const SDL_Rect* rect, Uint32 format, void* pixels, int pitch );
            void Present( );
            /*@}*/

            /**
             *  \name SDLU functions
             *
             *  \sa SDLU_render.h
             */
            /*@{*/
            /** Get the window associated with the renderer. **/
            SDL_Window* GetWindow( );

            /* Map pixel values */
            Uint32 MapRGBA( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
            Uint32 MapRGB ( Uint8 r, Uint8 g, Uint8 b );

            /* The text rendering API */
            int RenderText( int x, int y, const char* format, ... );
            int RenderTextVa( int x, int y, const char* format, va_list arg );
            int RenderText( int x, int y, std::string format, ... );
            int RenderTextVa( int x, int y, std::string format, va_list arg );
            void SetFontSize( Uint32 size );
            int GetFontSize( );

            int SetTruetypeFont( TTF_Font* font );
            int SetTruetypeFontFile( const char* font, int size );
            TTF_Font* GetTruetypeFont( );
            int SetTruetypeFontFile( std::string font, int size );

            /* SDLU_LoadTexture */
            SDL_Texture* LoadTextureWithColorkey( const char* fname, SDL_Color colorkey );
            SDL_Texture* LoadTexture( const char* fname );
            SDL_Texture* LoadTextureWithColorkey( std::string fname, SDL_Color colorkey );
            SDL_Texture* LoadTexture( std::string fname );
            /* Rendering commands */
            int CopyTexture( SDL_Texture* texture, int x, int y );
            int CopyTexture( SDLU::Texture* texture, int x, int y );
            int DrawCircle( int cx, int cy, int r );
            int DrawOutlineRect( SDL_Rect rect, SDL_Color outline, SDL_Color fill );
            void Begin( int mode );
            void SetPoint( int x, int y );
            void SetPoints( SDL_Point* points, int num_points );
            int End( );
            int FillPolygon( SDL_Point* points, int n );
            int DrawPolygon( SDL_Point* points, int n );
            int MultiCopy( SDL_Texture*, SDL_Rect*, SDL_Rect*, int, const char* );
            int MultiCopy( SDLU::Texture*, SDL_Rect*, SDL_Rect*, int, const char* );
            int MultiCopy( SDL_Texture*, SDL_Rect*, SDL_Rect*, int, std::string );
            int MultiCopy( SDLU::Texture*, SDL_Rect*, SDL_Rect*, int, std::string );

            int GL_CacheState( void );
            int GL_RestoreState( void );
            /*@}*/
    };

    /**
     *  \brief Wrapper class for the SDLU_Button structure
     */
    class DECLSPEC Button {
        private:
            /** The original button. **/
            SDLU_Button* button;

        public:

            /** Empty constructor -- do not use. **/
            Button( );

            /* SDLU_CreateButton(sdl_window, text, SDLU_BUTTON_TEXT | flags) */
            Button( SDL_Window* window, const char* text, Uint32 flags );
            Button( SDLU::Window* window, const char* text, Uint32 flags );
            Button( SDL_Window* window, std::string text, Uint32 flags );
            Button( SDLU::Window* window, std::string text, Uint32 flags );

            /* SDLU_CreateButton(sdl_window, sdl_texture, SDLU_BUTTON_IMAGE|flags */
            Button( SDL_Window* window, SDL_Texture* image, Uint32 flags );
            Button( SDLU::Window* window, SDL_Texture* image, Uint32 flags );
            Button( SDL_Window* window, SDLU::Texture* image, Uint32 flags );
            Button( SDLU::Window* window, SDLU::Texture* image, Uint32 flags);

            /** Constructor from original structure. **/
            Button( SDLU_Button* button);

            /** Destructor. **/
            ~Button( );

            /** Get the original button structure. **/
            SDLU_Button *GetButton( );

            /* The Button API */
            Uint32 GetFlags( );

            int Render( );
            int GetState( );

            int SetGeometry( int x, int y, int w, int h );
            int GetGeometry(int *x, int *y, int *w, int *h);

            int SetHotkey(SDL_Scancode hotkey);

            int SetStyles( SDLU_Styles* );
            int GetStyles( SDLU_Styles* );

            int SetImage( SDL_Texture* image );
            int SetImage( SDLU::Texture* image );
            int GetImage( SDL_Texture** );
            int GetImage( SDLU::Texture** );

            int Hide(int hide);

            int SetCallback( int type, SDLU_Callback callback, void *arg );
            int DelCallback( int type );

            int GetAction( int type );
            int SetAction( int type, int action );

            int AddData(const char* key, void* value);
            void* GetData(const char* key);
            int DelData(const char* key);

            int AddData(std::string* key, void* value);
            void* GetData(std::string* key);
            int DelData(std::string* key);

            int SetText( std::string text );
    };

    /**
     *  \brief Wrapper class for the SDLU_Sprite structure
     */
    class DECLSPEC Sprite {
        private:
            SDLU_Sprite* sprite;

        public:

            /**
             *  Constructors
             */
            /** empty constructor, do not use **/
            Sprite( );

            /** SDLU_CreateSprite() **/
            Sprite( SDL_Renderer*  , SDL_Texture*, int );
            Sprite( SDLU::Renderer*, SDL_Texture*, int );
            Sprite( SDL_Renderer*  , SDLU::Texture*, int );
            Sprite( SDLU::Renderer*, SDLU::Texture*, int );

            /** SDLU_CreateSpriteFromRW() **/
            Sprite( SDL_Renderer*  , SDL_RWops*  , int, int);
            Sprite( SDLU::Renderer*, SDL_RWops*  , int, int);
            Sprite( SDL_Renderer*  , SDLU::RWops*, int, int);
            Sprite( SDLU::Renderer*, SDLU::RWops*, int, int);

            /** SDLU_CreateSpriteFromFile() **/
            Sprite( SDL_Renderer*  , const char* , int );
            Sprite( SDLU::Renderer*, const char* , int );
            Sprite( SDL_Renderer*  , std::string , int );
            Sprite( SDLU::Renderer*, std::string , int );

            /** Create from SDLU_Sprite structure **/
            Sprite( SDLU_Sprite * );

            /** Destructors **/
            ~Sprite( );

            /** Get the original SDLU_Sprite structure **/
            SDLU_Sprite* GetSprite( );

            /* The Sprite API */
            int SetGeometry( int, int, int, int );
            int GetGeometry( int*, int*, int *, int*);

            int SetVelocity( double, double );
            int GetVelocity( double*, double* );
            int SetDirection( double, double );
            int GetDirection( double* );

            int SetAdvance( int );
            int GetAdvance( int* );

            int Pause( int );

            int SetMap( SDL_Rect*, int );
            int GetMap( SDL_Rect* );

            int SetFrameMode( int );
            int GetFrameMode( );

            int DrawRotated( int );

            int SetRenderFunc( int (*)(SDLU_Sprite*) );
            int SetUpdateFunc( int (*)(SDLU_Sprite*) );
            int SetMoveFunc  ( int (*)(SDLU_Sprite*) );

            SDL_Rect GetSourceRect( );

            int Move( );
            int Render( );
            int Update( );

            int AddData(const char* key, void* value);
            void* GetData(const char* key);
            int DelData(const char* key);

            int AddData(std::string* key, void* value);
            void* GetData(std::string* key);
            int DelData(std::string* key);
    };

    /**
     *  \brief Wrapper class for the SDL_Texture structure
     */
    class DECLSPEC Texture {
        private:
            SDL_Texture* texture;

        public:
            /** empty constructor, do not use **/
            Texture( );

            /** SDL_CreateTexture() **/
            Texture( SDL_Renderer*, Uint32, int, int, int );
            Texture( SDLU::Renderer*, Uint32, int, int, int );

            /** SDL_CreateTextureFromSurface() **/
            Texture( SDL_Renderer*, SDL_Surface* );
            Texture( SDLU::Renderer*, SDL_Surface* );

            /** SDLU_LoadTexture() **/
            Texture( SDL_Renderer*, const char* );
            Texture( SDLU::Renderer*, const char* );
            Texture( SDL_Renderer*, std::string );
            Texture( SDLU::Renderer*, std::string );

            /** SDLU_LoadTextureWithColorkey() **/
            Texture( SDL_Renderer*, const char*, SDL_Color );
            Texture( SDLU::Renderer*, const char*, SDL_Color );
            Texture( SDL_Renderer*, std::string, SDL_Color );
            Texture( SDLU::Renderer*, std::string, SDL_Color );

            /** From existing SDL_Texture* **/
            Texture( SDL_Texture* );

            /** destructor **/
            ~Texture( );

            /** get the SDL_Texture **/
            SDL_Texture* GetTexture( );

            /**
             *  SDL2 functions
             *  Refer to 'SDL2/SDL_render.h' for documentation
             */
            int Query( Uint32*, int*, int*, int* );
            int SetColorMod( Uint8, Uint8, Uint8 );
            int GetColorMod( Uint8*, Uint8*, Uint8* );
            int SetAlphaMod( Uint8 );
            int GetAlphaMod( Uint8* );
            int SetBlendMode( SDL_BlendMode );
            int GetBlendMode( SDL_BlendMode * );
            int Update( const SDL_Rect*, const void*, int );
            int Lock( const SDL_Rect*, void **, int * );
            void Unlock( );

            int GL_Bind( float* texw, float* texh );
            int GL_Unbind( );

            /**
             *  SDLU functions
             *  See 'SDLU_render.h' for documentation
             */
            int GetSize( int*, int* );
    };

    /**
     *  \brief Wrapper for SDLU_IniHandler
     */
    class DECLSPEC IniHandler {
        private:
            SDLU_IniHandler* handler;

        public:
            /* create new handler */
            IniHandler(void);

            /* LoadIni() */
            IniHandler(SDL_RWops*, int freesrc);
            IniHandler(SDLU::RWops*, int freesrc);
            IniHandler(const char*);
            IniHandler(std::string);

            /* from existing handler */
            IniHandler(SDLU_IniHandler* handler);

            /* destructor */
            ~IniHandler(void);

            /* get original structure */
            SDLU_IniHandler *GetIniHandler(void);

            int SetProperty(const char*, const char*, const char*);
            const char* GetProperty(const char*, const char*);
            int DelProperty(const char*, const char*);
            int DelSection(const char*);

            int SetProperty(std::string, std::string, std::string);
            std::string GetProperty(std::string, std::string);
            int DelProperty(std::string, std::string);
            int DelSection(std::string);

            /* save ini */
            int Save(SDL_RWops *file, int freesrc);
            int Save(SDLU::RWops *file, int freesrc);
            int Save(const char* file);
            int Save(std::string file);
    };

    class DECLSPEC RWops {
        private:
            SDL_RWops* rwops;

        public:
            RWops(void);
            RWops(const char* file, const char* mode);
            RWops(std::string file, std::string mode);
            RWops(FILE* fp, SDL_bool autoclose);
            RWops(void* mem, int size);
            RWops(const void* mem, int size);

            RWops(SDL_RWops*);

            ~RWops(void);

            SDL_RWops* GetRWops(void);

            Sint64 size(void);
            Sint64 seek(Sint64 offset, int whence);
            size_t read(void* ptr, size_t size, size_t maxnum);
            size_t write(const void* ptr, size_t size, size_t num);
    };

    class DECLSPEC Turtle {
        private:
            SDLU_Turtle* turtle;

        public:
            Turtle();
            Turtle(SDL_Renderer*);
            Turtle(SDLU::Renderer*);
            Turtle(SDLU_Turtle*);

            ~Turtle(void);

            SDLU_Turtle* GetTurtle();

            int SetDrawColor(Uint8, Uint8, Uint8, Uint8);
            int SetDrawBlendMode(SDL_BlendMode);
            int Move(int);
            int SetPosition(int,int);
            int Rotate(int);
            int Reset(void);
            int SetDirection(int);
    };

    class DECLSPEC ComboBox {
        private:
            SDLU_ComboBox* combobox;

        public:
            ComboBox();
            ComboBox(SDL_Window*);
            ComboBox(SDLU::Window*);
            ComboBox(SDLU_ComboBox*);

            ~ComboBox();

            SDLU_ComboBox* GetComboBox();

            int SetGeometry(int x, int y, int w, int h);
            int SetCallback(SDLU_Callback callback, void* arg);

            int SetStyles( SDLU_Styles* styles );
            int GetStyles( SDLU_Styles* styles );

            int Render();

            int AddItem(const char* item);
            int DelItem(const char* item);
            int AddItem(std::string item);
            int DelItem(std::string item);
    };

} /* namespace SDLU */

#endif /* SDLU_CXX */

#include "close_code.h"

#endif /* SDLU_CXX_H */
