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

#ifndef SDLU_FILESYSTEM_WINDOWS_C_H
#define SDLU_FILESYSTEM_WINDOWS_C_H

#include "SDLU.h"
#include <Windows.h>

typedef struct SDLU_Directory {
    HANDLE handle;
    HANDLE handleW;

    SDLU_FileInfo *fileinfo;

    SDL_bool read_first;

    SDL_bool ignore_dots;
} SDLU_Directory;

SDLU_Directory * WIN_OpenDirectory(const char *dirname, SDL_bool ignore_dots);
SDLU_Directory * WIN_OpenDirectoryW(const wchar_t *dirname, SDL_bool ignore_dots);
SDLU_FileInfo * WIN_NextFile(SDLU_Directory *dir);
void WIN_CloseDirectory(SDLU_Directory *dir);

int WIN_CreateDirectory(const char* dirname, Uint32 mode);
int WIN_CreateDirectoryW(const wchar_t *dirname, Uint32 mode);

#endif /* SDLU_FILESYSTEM_WINDOWS_C_H */
