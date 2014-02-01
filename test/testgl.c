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

/*
 * testgl: A test program for the SDL Utility library
 */

/* Create a GL texture from an SDL surface and render it */

#include "SDLU.h"
#include "SDL_opengl.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

SDL_Window* window;
SDL_GLContext context;
SDL_Surface* surface;
SDL_bool done = SDL_FALSE;
SDL_Event event;

/** initialize the GL state **/
void GL_InitState(int w, int h)
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport( 0, 0, w, h );
    glOrtho(0, w, h, 0, -1, 1);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
}

/** called at exit to cleanup **/
void cleanup( void )
{
    if (window) SDL_DestroyWindow(window);
    if (context) SDL_GL_DeleteContext(context);
    if (surface) SDL_FreeSurface(surface);
    SDL_Quit();
}

int main(int argc, char** argv)
{
    GLuint texture;
    GLfloat w, h; /* width and height of the texture */

    /** Initialize SDL **/
    SDL_CHECK( SDL_Init(SDL_INIT_VIDEO) != -1 );
    atexit( cleanup );

    window = SDL_CreateWindow("", 100, 100, 320, 240, SDL_WINDOW_OPENGL);
    SDL_CHECK(window);

    context = SDL_GL_CreateContext( window );
    SDL_CHECK(context);

    surface = SDL_LoadBMP(TUX_BMP);
    SDL_CHECK(surface);

    /** create the texture from the surface **/
    texture = SDLU_GL_LoadTexture( surface, &w, &h );
    SDL_CHECK(texture);

    /** Initialize OpenGL state **/
    GL_InitState(320, 240);

    /** render a textured rectangle **/
    glBindTexture( GL_TEXTURE_2D, texture );
    glBegin( GL_QUADS );
        glTexCoord2f(0, 0);         glVertex2f(   0,   0);
        glTexCoord2f(w, 0);         glVertex2f( 320,   0);
        glTexCoord2f(w, h);         glVertex2f( 320, 240);
        glTexCoord2f(0, h);         glVertex2f(   0, 240);
    glEnd();

    /** update screen **/
    SDL_GL_SwapWindow( window );

    /** wait for quit event **/
    while( done == SDL_FALSE )
    {
        SDL_PollEvent( &event );

        if (event.type == SDL_QUIT)
            done = SDL_TRUE;
    }

    exit(0);
}

