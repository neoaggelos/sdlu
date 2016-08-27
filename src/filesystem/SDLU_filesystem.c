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

#if defined( FILESYSTEM_WINDOWS )
# include "SDLU_filesystem_windows_c.h"
#elif defined( FILESYSTEM_DIRENT )
# include "SDLU_filesystem_dirent_c.h"
#endif

#define UNUSED(x) (void)(x)

#include <string.h>
#include <wchar.h>

static SDL_bool
string_endsin(const char* str, const char* end)
{
    size_t i;
    size_t startpos = SDL_strlen(str) - SDL_strlen(end);

    for (i = 0; i < SDL_strlen(end); i++)
        if (str[startpos + i] != end[i]) return SDL_FALSE;

    return SDL_TRUE;
}

static SDL_bool
wstring_endsin(const wchar_t* str, const wchar_t* end)
{
    size_t i;
    size_t startpos = wcslen(str) - wcslen(end);

    for (i = 0; i < wcslen(end); i++)
        if (str[startpos + i] != end[i]) return SDL_FALSE;

    return SDL_TRUE;
}

SDLU_Directory *
SDLU_OpenDirectory(const char* dirname, SDL_bool ignore_dots)
{
#if defined( FILESYSTEM_WINDOWS )
    return WIN_OpenDirectory(dirname, ignore_dots);
#elif defined( FILESYSTEM_DIRENT )
    return DIR_OpenDirectory(dirname, ignore_dots);
#else
    return NULL;
#endif
}

SDLU_Directory *
SDLU_OpenDirectoryW(const wchar_t* dirname, SDL_bool ignore_dots)
{
#if defined( FILESYSTEM_WINDOWS )
    return WIN_OpenDirectoryW(dirname, ignore_dots);
#elif defined( FILESYSTEM_DIRENT )
    return DIR_OpenDirectoryW(dirname, ignore_dots);
#else
    return NULL;
#endif
}

SDLU_FileInfo*
SDLU_NextFile(SDLU_Directory *dir)
{
#if defined( FILESYSTEM_WINDOWS )
    return WIN_NextFile(dir);
#elif defined( FILESYSTEM_DIRENT )
    return DIR_NextFile(dir);
#else
    return NULL;
#endif
}

SDLU_FileInfo*
SDLU_NextFileWithExtension(SDLU_Directory* dir, const char* ext)
{
    SDLU_FileInfo *info;

    while ((info = SDLU_NextFile(dir)) && !string_endsin(info->filename, ext))
        ;

    return info;
}

SDLU_FileInfo*
SDLU_NextFileWithExtensionW(SDLU_Directory* dir, const wchar_t* ext)
{
    SDLU_FileInfo *info;

    while ((info = SDLU_NextFile(dir)) && !wstring_endsin(info->filenameW, ext))
        ;

    return info;
}

void
SDLU_CloseDirectory(SDLU_Directory *dir)
{
#if defined( FILESYSTEM_WINDOWS )
    WIN_CloseDirectory(dir);
#elif defined( FILESYSTEM_DIRENT )
    DIR_CloseDirectory(dir);
#else
    UNUSED(dir);
#endif
}

int
SDLU_CreateDirectory(const char *dirname, Uint32 mode)
{
#if defined( FILESYSTEM_WINDOWS )
    WIN_CreateDirectory(dirname, mode);
#elif defined( FILESYSTEM_DIRENT )
    DIR_CreateDirectory(dirname, mode);
#else
    UNUSED(dirname);
    UNUSED(mode);
#endif
}

int
SDLU_CreateDirectoryW(const wchar_t *dirname, Uint32 mode)
{
#if defined( FILESYSTEM_WINDOWS )
    WIN_CreateDirectoryW(dirname, mode);
#elif defined( FILESYSTEM_DIRENT )
    DIR_CreateDirectoryW(dirname, mode);
#else
    UNUSED(dirname);
    UNUSED(mode);
#endif
}