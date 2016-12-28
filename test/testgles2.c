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
 *  testgles2: A test program for the SDL utility library
 */

/*
 * This program shows how to use OpenGLES2 with SDL2
 */

#include "SDL.h"
#include "SDL_opengles2.h"

#include <stdio.h>
#include <stdlib.h>

/******************************/

#define GLES_ATTRIB_POS  0
#define GLES_ATTRIB_COLOR     1

/******************************/

SDL_Event event;
SDL_bool done = SDL_FALSE;

/******************************/

GLuint  ES_LoadShader(const GLchar* src, GLenum type);
GLuint  ES_LoadProgram();
void    ES_Draw(GLuint program);

/******************************/

GLuint
ES_LoadShader(const GLchar* src, GLenum type)
{
    GLuint shader;
    GLint compiled;
    int info_log_l;
    char* info_log;

    /** create shader object **/
    shader = glCreateShader(type);
    if (!shader)
        return 0;

    /** compile shader **/
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    /** handle errors **/
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_l);
        if (info_log_l > 1) {
            info_log = (char*) malloc( sizeof(char) * info_log_l);
            glGetShaderInfoLog(shader, info_log_l, NULL, info_log);
            SDL_Log("Compile error: %s\n", info_log);
            free(info_log);
        }
        glDeleteShader(shader);
        return 0;
    }

    /** return shader object **/
    return shader;
}

GLuint
ES_LoadProgram()
{
    GLuint v_shader, f_shader;
    GLuint program;
    GLint linked;
    int info_log_l;
    char* info_log;

    /*** VERTEX SHADER ***/
    const GLchar* v_shader_src =
        "attribute vec4 a_position;     \n"
        "attribute vec4 a_color;        \n"
        "varying vec4 v_color;          \n"

        "void main() {                  \n"
        "   gl_Position = a_position;   \n"
        "   v_color = a_color;          \n"
        "}                              \n";

    /*** FRAGMENT SHADER ***/
    const GLchar* f_shader_src =
        "precision mediump float;       \n"
        "varying vec4 v_color;          \n"

        "void main() {                  \n"
        "   gl_FragColor = v_color;     \n"
        "}                              \n";

    /** create program object **/
    program = glCreateProgram();
    if (!program)
        return 0;

    /** load shaders **/
    v_shader = ES_LoadShader(v_shader_src, GL_VERTEX_SHADER);
    f_shader = ES_LoadShader(f_shader_src, GL_FRAGMENT_SHADER);

    /** attach shaders **/
    glAttachShader(program, v_shader);
    glAttachShader(program, f_shader);

    /** bind attributes **/
    glBindAttribLocation(program, GLES_ATTRIB_POS, "a_position");
    glBindAttribLocation(program, GLES_ATTRIB_COLOR, "a_color");

    /** link program **/
    glLinkProgram(program);

    /** handle errors **/
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_l);
        if (info_log_l > 1) {
            info_log = (char*) malloc( info_log_l * sizeof(char) );
            glGetProgramInfoLog(program, info_log_l, NULL, info_log);
            SDL_Log("Link error: %s\n", info_log);
            free(info_log);
        }
        glDeleteProgram(program);
        return 0;
    }

    /** return program object **/
    return program;
}

void
ES_Draw(GLuint program)
{
    GLfloat vertices[] = {
           0,  0.5, 0,          /** top             **/
        -0.5, -0.5, 0,          /** bottom-left     **/
         0.5, -0.5, 0           /** bottom-rigth    **/
    };

    glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(GLES_ATTRIB_POS, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttrib4f(GLES_ATTRIB_COLOR, 1, 0, 0, 1);
    glEnableVertexAttribArray(GLES_ATTRIB_POS);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/******************************/

int main(int argc, char** argv)
{

    SDL_Window* window;     /** the application window  **/
    SDL_GLContext context;  /** the ES2 context         **/
    GLuint program;         /** the ES2 program         **/

    /** Initialize SDL **/
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Could not initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }
    atexit(SDL_Quit);

    /** Set attributes for an OpenGLES2 context**/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /** Create window **/
    window = SDL_CreateWindow("SDL2 - OpenGL ES 2",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_OPENGL
    );
    if (!window) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        exit(-1);
    }

    /** Create context **/
    context = SDL_GL_CreateContext(window);
    if (!context) {
        SDL_Log("Could not create OpenGLES2 context: %s\n", SDL_GetError());
        exit(-1);
    }

    /** Load the GLES2 program **/
    program = ES_LoadProgram();
    if (!program) {
        SDL_Log("Error loading program\n");
        exit(-1);
    }

    /** Initialize GL state **/
    glViewport(0, 0, 640, 480);
    glClearColor(0,0,0,1);

    /** draw the scene **/
    ES_Draw(program);

    /** Main loop **/
    while( !done )
    {
        /** handle quit event **/
        if (SDL_PollEvent( &event )) {
            if (event.type == SDL_QUIT)
                done = SDL_TRUE;
        }

        /** update window **/
        SDL_GL_SwapWindow( window );
        SDL_Delay(20);
    }

    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);

    exit(0);
}
