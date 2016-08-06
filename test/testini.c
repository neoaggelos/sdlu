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
 * testini: A test program for the SDL Utility library
 */

/*
 * Makes usage of the ini file handling API
 */

#include "SDLU.h"
#include "common.h"

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    char *a, *b, *c, *d, *e, *f, *g;

    /** Create a new empty ini handler **/
    SDLU_IniHandler* handler = SDLU_CreateIni();
    SDL_CHECK(handler);

    /** Set some properties **/
    SDLU_SetIniProperty(&handler, NULL, "version", "2.0.1");
    SDLU_SetIniProperty(&handler, NULL, "savename", "kernal8");

    SDLU_SetIniProperty(&handler, "user", "username", "kernal8");
    SDLU_SetIniProperty(&handler, "user", "battle-points", "900");
    SDLU_SetIniProperty(&handler, "user", "last-visit", "14th Dec 2013");

    /** assert username is set correctly **/
    a = (char*)SDLU_GetIniProperty(handler, "user", "username");
    SDL_assert(a != NULL);

    /** assert that deletion works **/
    SDLU_DelIniProperty(&handler, "user", "last-visit");
    b = (char*)SDLU_GetIniProperty(handler, "user", "last-visit");
    SDL_assert(b == NULL);

    /** delete full section **/
    SDLU_DelIniSection(&handler, "user");
    c = (char*)SDLU_GetIniProperty(handler, "user", "username");
    SDL_assert((c == NULL) && (handler->num_sections == 1));

    /** create new section **/
    SDLU_SetIniProperty(&handler, "program", "important-id", "real-important-id-to-keep");
    d = (char*)SDLU_GetIniProperty(handler, "program", "important-id");
    SDL_assert(d != NULL && handler->num_sections == 2);

    /*** success ***/
    SDLU_Message("Passed all tests successfully!");

    SDLU_DestroyIni(handler);
    return 0;
}
