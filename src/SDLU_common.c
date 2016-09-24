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

#include "SDLU_common.h"
#include "SDLU.h"

#define SDLU_MAXLEN 1024

/*
 * don't complain about '(int) = (int) * (float)'
 */
#ifdef _MSC_VER
# pragma warning (disable: 4244)
#endif

int
SDLU_vasprintf(char** s, const char* format, va_list arg)
{
    char tmp[SDLU_MAXLEN];
    size_t len;

    SDL_vsnprintf(tmp, SDLU_MAXLEN-1, format, arg);
    len = SDL_strlen(tmp) + 1;

    *s = (char*) SDL_malloc(sizeof(char) * len);

    SDL_memcpy(*s, tmp, len);
    return len;
}

char*
SDLU_format(const char* format, ...)
{
    char* ret;
    va_list arg;

    va_start(arg, format);
    SDLU_vasprintf(&ret, format, arg);
    va_end(arg);

    return ret;
}

SDL_Rect
SDLU_GetScaledRect(SDL_Renderer* renderer, SDL_Rect orig, SDL_bool clip)
{
    SDL_Rect result;
    SDL_Window* window;
    SDL_Rect viewport;
    int ww, wh;         /** window width, height **/
    float sx, sy;       /** scale **/
    int lw, lh;

    result = orig;
    window = SDLU_GetWindow(renderer);
    SDL_GetWindowSize(window, &ww, &wh);
    SDL_RenderGetLogicalSize(renderer, &lw, &lh);
    SDL_RenderGetScale(renderer, &sx, &sy);

    /** add padding if needed by the viewport **/
    SDL_RenderGetViewport(renderer, &viewport);
    result.x += viewport.x;
    result.y -= viewport.y;

    if (sx == 1 && sy == 1) {
        result.y += wh - viewport.h;
    }

    if (sy !=1 && lw && lh && viewport.y) {
        result.y += 2 * viewport.y;
    }

    /** scale if needed by the renderer **/
    if (sx != 1.0 || sy != 1.0) {
        result.x *= sx;
        result.y *= sy;
        result.w *= sx;
        result.h *= sy;
    }

    /** Clip rect against the viewport, if requested **/
    if (clip) {
        SDL_Rect cliprect;
        if (sx == 1 && sy == 1) {
            cliprect = viewport;
        } else {
            cliprect = SDLU_CreateRect(0, 0, ww, wh);
        }

        SDL_IntersectRect(&cliprect, &result, &result);
    }

    return result;
}

char*
SDLU_ReadFile(SDL_RWops* rwops)
{
    char* buffer;
    Sint64 size = SDL_RWsize(rwops);

    buffer = (char*) SDL_malloc(sizeof(char) * size);
    SDL_assert(buffer);

    rwops->read(rwops, buffer, sizeof(char), size);
    return buffer;
}

SDLU_Styles*
SDLU_GetDefaultStyles()
{
    SDLU_Styles *styles = (SDLU_Styles*) SDL_malloc(sizeof(SDLU_Styles));

    if (styles == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    styles->title = "text";
    styles->font = SDLU_LoadFont(NULL, 20, 1);
	styles->freefont = SDL_TRUE;
    styles->text_color = SDLU_CreateRGBA( 255, 255, 255, 255 );
    styles->fill_color = SDLU_CreateRGBA( 100, 100, 100, 255 );
    styles->box_color  = SDLU_CreateRGBA( 255, 255, 255, 255 );
    styles->blendmode  = SDL_BLENDMODE_NONE;

    return styles;
}
