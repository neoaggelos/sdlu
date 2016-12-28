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

/* 
 * OpenGL symbols - the values are the same for all implementations and the
 * OpenGL headers are not included, so we have to define them here
 */

#ifndef SDLU_OPENGL_C_H
#define SDLU_OPENGL_C_H

#define GL_UNSIGNED_BYTE 0x1401
#define GL_RGBA 0x1908
#define GL_NEAREST 0x2600
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_2D 0x0DE1
#define GL_EXTENSIONS 0x1F03
#define GL_BLEND 0x0BE2

typedef unsigned char GLubyte;
typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef int GLint;
typedef void GLvoid;
typedef float GLfloat;

#ifdef __APPLE__
typedef void* GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif

#if defined(_MSC_VER) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
# define APIENTRY   __stdcall
#else
# define APIENTRY
#endif

typedef GLubyte* (APIENTRY *GL_GETSTRING)(GLenum);
typedef void (APIENTRY *GL_BINDTEXTURE)(GLenum, GLuint);
typedef void (APIENTRY *GL_COLOR4F)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRY *GL_DISABLE)(GLenum);
typedef void (APIENTRY *GL_GENTEXTURES)(GLsizei, GLuint*);
typedef void (APIENTRY *GL_POPMATRIX)(void);
typedef void (APIENTRY *GL_PUSHMATRIX)(void);
typedef void (APIENTRY *GL_TEXIMAGE2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (APIENTRY *GL_TEXPARAMETERI)(GLenum, GLenum, GLint);
typedef void (APIENTRY *GL_USEPROGRAM)(GLuint);
typedef void (APIENTRY *GL_USEPROGRAMOBJECTARB)(GLhandleARB);

#define load_gl_func(func, type)                        \
    func = (type) SDL_GL_GetProcAddress(#func);         \
    if (!func) {                                        \
        SDLU_ExitError("could not load " #func, 0);     \
    }

#endif /* SDLU_OPENGL_C_H */
