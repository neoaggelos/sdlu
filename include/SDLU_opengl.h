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
 *  \file SDLU_opengl.h
 *
 *  \brief Defines OpenGL related functions
 */

#ifndef SDLU_OPENGL_H
#define SDLU_OPENGL_H

#include "SDLU_config.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Create an OpenGL texture from an SDL_Surface
 *
 *  For NPOT texture handling, see SDLU_HINT_GL_TEXTURE_ADD_PADDING
 *
 *  \param surface the image to create a texture from
 *  \param texw will be filled with the width of the texture
 *  \param texh will be filled with the height of the texture
 *
 *  \return the texture id on success, 0 on error
 *
 *  \note Refrain from passing a surface that has a colorkey
 *
 *  \sa SDLU_GL_LoadTextureFromFile()
 *  \sa SDLU_HINT_GL_TEXTURE_ADD_PADDING
 */
extern DECLSPEC unsigned int SDLCALL SDLU_GL_LoadTexture(
        SDL_Surface* surface,
        float* texw, float* texh
);

/**
 *  \brief Same as SDLU_GL_LoadTexture(), but load the image data from a file
 *
 *  \note 'filename' should be a BMP file. If the image is in PNG or any other
 *  format, first load it into an SDL_Surface and then use SDLU_GL_LoadTexture()
 *
 *  \sa SDLU_GL_LoadTexture()
 */
extern DECLSPEC unsigned int SDLCALL SDLU_GL_LoadTextureFromFile(
        const char* filename,
        float* texw, float* texh
);

/**
 *  \brief Cache the internal state of the renderer
 *
 *  Using SDLU_GL_RenderCacheState() with SDLU_GL_RenderRestoreState() enables
 *  you to mix pure OpenGL calls with the SDL2 Render API.
 *
 *  FIXME: This function may or may not work under different operating systems,
 *  depending on the system configuration and the OpenGL drivers. This has been
 *  tested, and works as expected, on Linux and Mac OS X.
 *
 *  \param renderer Renderer whose state to cache
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GL_RenderRestoreState()
 */
extern DECLSPEC int SDLCALL SDLU_GL_RenderCacheState(SDL_Renderer* renderer);

/**
 *  \brief Restore the internal state of the renderer
 *
 *  Using SDLU_GL_RenderCacheState() with SDLU_GL_RenderRestroreState() enables
 *  you to mix pure OpenGL calls with the SDL2 Render API.
 *
 *  An important thing to know is that these functions only save and restore the
 *  "basic" state required to get things working. If you explicitly change the
 *  state with glEnable() calls, make sure that you leave everything as is after
 *  you have finished drawing. See the following for a small example:
 *
 *  \code
 *  ... SDL2 stuff ...
 *  SDLU_GL_RenderCacheState(renderer);         // cache state
 *  glEnable(GL_BLEND);                         // we enable GL_BLEND
 *  ... OpenGL stuff ...
 *  glDisable(GL_BLEND);                        // we must restore GL_BLEND
 *  SDLU_GL_RenderRestoreState(renderer);       // restore state
 *  ... SDL2 stuff ...
 *  \endcode
 *
 *  \param renderer Renderer whose state to restore
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GL_RenderCacheState()
 */
extern DECLSPEC int SDLCALL SDLU_GL_RenderRestoreState(SDL_Renderer* renderer);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_OPENGL_H */
