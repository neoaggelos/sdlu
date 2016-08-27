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

#ifndef SDLU_FILESYSTEM_DIRENT_C_H
#define SDLU_FILESYSTEM_DIRENT_C_H

#include "SDLU.h"
#include <dirent.h>

typedef struct SDLU_Directory {
  DIR *dir;

  SDLU_FileInfo *info;

  SDL_bool ignore_dots;
} SDLU_Directory;

SDLU_Directory *DIR_OpenDirectory(const char* dirname, SDL_bool ignore_dots);
SDLU_Directory *DIR_OpenDirectoryW(const wchar_t* dirname, SDL_bool ignore_dots);
SDLU_FileInfo *DIR_NextFile(SDLU_Directory *dir);
void DIR_CloseDirectory(SDLU_Directory *dir);

int DIR_CreateDirectory(const char* dirname, Uint32 mode);
int DIR_CreateDirectoryW(const wchar_t *dirname, Uint32 mode);

#endif /* SDLU_FILESYSTEM_DIRENT_C_H */
