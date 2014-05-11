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
#include <stdio.h>

#include "gl_defs.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wpointer-sign"
#endif

/* silence errors in SDL_GL_GetProcAddress */
#ifdef _MSC_VER
#pragma warning (disable: 4152)
#endif

/** return the first power of two equal to or bigger than i **/
static int add_padding( int i )
{
    int result = 1;
    while( result < i ){
        result = result << 1;
    }
    return result;
}

GLuint
SDLU_GL_LoadTexture(SDL_Surface* surface, float *texw, float *texh)
{
    GLuint texture;
    int result;
    SDL_Surface* temp;
    SDL_BlendMode blendmode;
    Uint8 alpha;
    int width;
    int height;
    const char* hint;       /* SDLU_HINT_GL_TEXTURE_ADD_PADDING */
    int padding;

    /* required opengl calls that are dynamically loaded */
    GL_GETSTRING glGetString;
    GL_GENTEXTURES glGenTextures;
    GL_BINDTEXTURE glBindTexture;
    GL_TEXIMAGE2D glTexImage2D;
    GL_TEXPARAMETERI glTexParameteri;

    load_gl_func(glGetString, GL_GETSTRING);
    load_gl_func(glGenTextures, GL_GENTEXTURES);
    load_gl_func(glBindTexture, GL_BINDTEXTURE);
    load_gl_func(glTexImage2D, GL_TEXIMAGE2D);
    load_gl_func(glTexParameteri, GL_TEXPARAMETERI);

    if (surface == NULL)
        SDLU_ExitError("invalid parameter 'surface'", 0);

    /* check whether we have to add padding */
    hint = SDLU_GetHint(SDLU_HINT_GL_TEXTURE_ADD_PADDING);
    if (SDL_strcmp(hint, "always") == 0) {
        padding = 1;
    } else if (SDL_strcmp(hint, "never") == 0) {
        padding = 0;
    } else {
        const char* glext;      /* list of GL_EXTENSIONS */
        char *arb, *oes;
        glext = glGetString(GL_EXTENSIONS);

        if (!glext) {
            SDLU_Log("Could not get supported extensions\n");
            padding = 1;
        } else {
            arb = SDL_strstr(glext, "GL_ARB_texture_non_power_of_two");
            oes = SDL_strstr(glext, "GL_OES_texture_npot");

            /*
             * add padding if none of the extensions for npot textures are
             * supported by the implementation
             */
            padding = (!arb && !oes);
        }
    }

#ifdef _DEBUG
    if (padding) {
        SDLU_Log("Will add padding to the texture");
    } else {
        SDLU_Log("Will not add padding to the texture");
    }
#endif

    /* add padding if needed */
    if (padding) {
        width = add_padding( surface->w );
        height = add_padding( surface->h );
    } else {
        width = surface->w;
        height = surface->h;
    }

    /* fill pointers with the texture width and height */
    if (texw) *texw = (float) surface->w / width;
    if (texh) *texh = (float) surface->h / height;

    /** create a temporary surface **/
    temp = SDL_CreateRGBSurface(0, width, height, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
            0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
#endif
    );
    if (temp == NULL)
        return 0;

    /** reset **/
    result = 0;

    /** temporarily remove blendmode and alpha from the image **/
    result |= SDL_GetSurfaceBlendMode( surface, &blendmode );
    result |= SDL_GetSurfaceAlphaMod(  surface, &alpha );

    result |= SDL_SetSurfaceBlendMode( surface, SDL_BLENDMODE_NONE);
    result |= SDL_SetSurfaceAlphaMod(  surface, 0xff );

    /** copy image to our temporary surface **/
    result |= SDL_BlitSurface(surface, NULL, temp, NULL);

    /** restore original properties **/
    result |= SDL_SetSurfaceBlendMode(surface, blendmode);
    result |= SDL_SetSurfaceAlphaMod(surface, alpha);

    if (result != 0) {
        SDL_FreeSurface(temp);
        SDLU_ExitError("Could not create temporary surface", 0);
    }

    glGenTextures( 1, &texture );

    if (!texture) {
        SDL_FreeSurface(temp);
        SDLU_ExitError("glGenTextures() failed", 0);
    }

    /** generate an OpenGL texture from the temporary surface **/
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                  GL_UNSIGNED_BYTE, temp->pixels);

    /** we no longer need this **/
    SDL_FreeSurface(temp);

    return texture;
}

GLuint
SDLU_GL_LoadTextureFromFile(const char* filename, float* texw, float* texh)
{
    SDL_Surface* tmp;
    GLuint texture;

    tmp = SDL_LoadBMP(filename);
    if (tmp == NULL) {
        SDLU_ExitError(
            SDLU_format("could not load BMP file: %s", SDL_GetError()), 0
        );
    }

    texture = SDLU_GL_LoadTexture(tmp, texw, texh);

    SDL_FreeSurface(tmp);

    return texture;
}

static const char*
get_renderer_backend(SDL_Renderer* renderer)
{
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);

    return info.name;
}

int
SDLU_GL_RenderCacheState(SDL_Renderer *renderer)
{
    const char* library = get_renderer_backend(renderer);

    /* Draw a fake point just to activate the renderer */
    SDL_RenderDrawPoint(renderer, -1, -1);

    if (SDL_strcmp(library, "opengl") == 0) {
        GL_PUSHMATRIX glPushMatrix;
        GL_USEPROGRAMOBJECTARB glUseProgramObjectARB;
        load_gl_func(glPushMatrix, GL_PUSHMATRIX);
        load_gl_func(glUseProgramObjectARB, GL_USEPROGRAMOBJECTARB);

        glUseProgramObjectARB(0);
        glPushMatrix();
    } else if (SDL_strcmp(library, "opengles") == 0) {
        GL_PUSHMATRIX glPushMatrix;
        load_gl_func(glPushMatrix, GL_PUSHMATRIX);

        glPushMatrix();
    } else if (SDL_strcmp(library, "opengles2") == 0) {
        GL_USEPROGRAM glUseProgram;
        load_gl_func(glUseProgram, GL_USEPROGRAM);

        glUseProgram(0);
    }

    return 0;
}

int
SDLU_GL_RenderRestoreState(SDL_Renderer *renderer)
{
    const char* library = get_renderer_backend(renderer);

    if (SDL_strcmp(library, "opengl") == 0) {
        GL_POPMATRIX glPopMatrix;
        GL_DISABLE glDisable;
        GL_COLOR4F glColor4f;

        load_gl_func(glPopMatrix, GL_POPMATRIX);
        load_gl_func(glDisable, GL_DISABLE);
        load_gl_func(glColor4f, GL_COLOR4F);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glPopMatrix();
        glDisable(GL_BLEND);
    } else if (SDL_strcmp(library, "opengles") == 0) {
        GL_POPMATRIX glPopMatrix;
        GL_DISABLE glDisable;
        GL_COLOR4F glColor4f;

        load_gl_func(glPopMatrix, GL_POPMATRIX);
        load_gl_func(glDisable, GL_DISABLE);
        load_gl_func(glColor4f, GL_COLOR4F);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glPopMatrix();
        glDisable(GL_BLEND);
    } else if (SDL_strcmp(library, "opengles2") == 0) {
        GL_DISABLE glDisable;

        load_gl_func(glDisable, GL_DISABLE);

        glDisable(GL_BLEND);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_RenderDrawPoint(renderer, -1, -1);

    return 0;
}
