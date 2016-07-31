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
 *  \file SDLU_filesystem.h
 *
 *  \brief The file system API
 */

#ifndef SDLU_FILESYSTEM_H
#define SDLU_FILESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL.h"
#include "begin_code.h"

typedef struct SDLU_Directory SDLU_Directory;

typedef enum {
    SDLU_REGULAR_FILE,
    SDLU_DIRECTORY,
    SDLU_SYMBOLIC_LINK
} SDLU_FileType;

typedef struct SDLU_FileInfo {
    char* filename;
    wchar_t* filenameW;

    SDLU_FileType filetype;
} SDLU_FileInfo;

extern DECLSPEC SDLU_Directory * SDLCALL SDLU_OpenDirectory(const char* dirname, SDL_bool ignore_dots);
extern DECLSPEC SDLU_Directory * SDLCALL SDLU_OpenDirectoryW(const wchar_t* dirname, SDL_bool ignore_dots);

extern DECLSPEC SDLU_FileInfo * SDLCALL SDLU_NextFile(SDLU_Directory *dir);
extern DECLSPEC SDLU_FileInfo * SDLCALL SDLU_NextFileWithExtension(SDLU_Directory *dir, const char* ext);
extern DECLSPEC SDLU_FileInfo * SDLCALL SDLU_NextFileWithExtensionW(SDLU_Directory *dir, const wchar_t* ext);

extern DECLSPEC void SDLCALL SDLU_CloseDirectory(SDLU_Directory *dir);


#include "close_code.h"

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILESYSTEM_H */
