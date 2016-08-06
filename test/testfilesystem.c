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
 * testfilesystem: A test program for the SDL utility library
 */

/*
 * Display the contents of a directory
 */

#include "SDLU.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    SDLU_Directory *dir = SDLU_OpenDirectory(".", SDL_TRUE);

    SDLU_FileInfo* info;

    printf("Contents of '.'\n------------\n");
    while(info = SDLU_NextFile(dir)) {
        printf("%s\n", info->filename);
    }

    exit(0);
}
