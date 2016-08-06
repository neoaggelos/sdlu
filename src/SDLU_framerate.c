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

#include "SDLU.h"
#include "SDLU_common.h"
#include <stdio.h>

/* Internal state variables */
static Uint32 is_init = 0;  /* To prevent SIGFPE */
static Uint32 fps = 0;      /* The desired framerate */
static Uint32 cap = 1;      /* Cap the framerate option */
static Uint32 frames = 0;   /* Counter of frames */
static Uint32 realfps = 0;  /* The real framerate of the application */
static Uint32 nowtime = 0;
static Uint32 start = 0;
static Uint32 verystart = 0;

void
SDLU_FPS_Init(int framerate)
{
    fps = ( framerate <= 0 ? SDLU_DEFAULT_FRAMERATE : framerate );
    realfps = fps;
    frames = 0;
    cap = 1;
    is_init = 1;
    verystart = SDL_GetTicks();
}

void
SDLU_FPS_Start( void )
{
    if (is_init == 0)
        SDLU_ExitError("framerate manager not initialized", );

    start = SDL_GetTicks();
    frames++;
}

void
SDLU_FPS_Cap( void )
{
    if (is_init == 0)
        SDLU_ExitError("framerate manager not initialized", );

    nowtime = SDL_GetTicks();

    /* Delay the time needed to cap the framerate */
    if ( cap == 1 && (nowtime - start < 1000 / fps))
        SDL_Delay( (int)(1000 / fps) - (int)(nowtime - start));

    /* Get the actual framerate */
    if (nowtime - verystart >= 1000 ) {
        realfps = (int)(1000* frames) / (int)(nowtime - verystart);
        frames = 0;
        verystart = nowtime;
    }
}

void
SDLU_FPS_ToggleCap( void )
{
    cap = !cap;
}

void
SDLU_FPS_SetCap( int enable )
{
    cap = ( enable ? 1 : 0 );
}

int
SDLU_FPS_GetFramerate( void )
{
    return fps;
}

int
SDLU_FPS_GetRealFramerate( void )
{
    return realfps;
}
