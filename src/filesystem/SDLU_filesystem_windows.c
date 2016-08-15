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

#ifdef FILESYSTEM_WINDOWS

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <wchar.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "SDLU.h"
#include "SDLU_common.h"
#include "SDLU_filesystem_windows_c.h"

static SDLU_FileType
WIN_GetFileType(const wchar_t* path)
{
    struct _stat st;
    
    if (_wstat(path, &st) == -1) {
        return SDLU_UNKNOWN_FILETYPE;
    }
    else if (st.st_mode & S_IFREG) {
        return SDLU_REGULAR_FILE;
    }
    else if (st.st_mode & S_IFDIR) {
        return SDLU_DIRECTORY;
    } else {
        return SDLU_UNKNOWN_FILETYPE;
    }
}

SDLU_Directory *
WIN_OpenDirectory(const char *dirname, SDL_bool ignore_dots)
{
    WIN32_FIND_DATAA da;
    WIN32_FIND_DATAW dw;
    size_t dirlen = SDL_strlen(dirname);

    SDLU_Directory *dir = (SDLU_Directory*) SDL_malloc(sizeof(SDLU_Directory));
    if (dir == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo = (SDLU_FileInfo*) SDL_malloc(sizeof(SDLU_FileInfo));

    dir->ignore_dots = ignore_dots;
    if (dir->fileinfo == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo->filename = NULL;
    dir->fileinfo->filenameW = NULL;

    char *fmt = (char*) SDL_malloc(sizeof(char) * (dirlen + 3));
    strcpy(fmt, dirname);
    fmt[dirlen] = '\\';
    fmt[dirlen + 1] = '*';
    fmt[dirlen + 2] = '\0';

    wchar_t *fmtW = (wchar_t*) SDL_malloc(sizeof(wchar_t) * (dirlen+3));
    mbstowcs(fmtW, fmt, dirlen+3);

    dir->handle = FindFirstFileA(fmt, &da);
    dir->handleW = FindFirstFileW(fmtW, &dw);

    SDL_free(fmt);
    SDL_free(fmtW);

    if (!dir->handle || !dir->handleW) {
        SDL_free(dir->fileinfo);
        SDL_free(dir);
        SDLU_ExitError("could not open directory", NULL);
    }

    if (ignore_dots && SDL_strcmp(da.cFileName, ".") && SDL_strcmp(da.cFileName, "..")) {
        dir->read_first = SDL_TRUE;
    }
    else {
        dir->read_first = SDL_FALSE;
        dir->fileinfo->filename = SDL_strdup(da.cFileName);
        dir->fileinfo->filenameW = _wcsdup(dw.cFileName);
        dir->fileinfo->filetype = WIN_GetFileType(dw.cFileName);
    }

    return dir;
}

SDLU_Directory *
WIN_OpenDirectoryW(const wchar_t *dirname, SDL_bool ignore_dots)
{
    WIN32_FIND_DATAA da;
    WIN32_FIND_DATAW dw;
    size_t dirlen = wcslen(dirname);

    SDLU_Directory *dir = (SDLU_Directory*) SDL_malloc(sizeof(SDLU_Directory));
    if (dir == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo = (SDLU_FileInfo*) SDL_malloc(sizeof(SDLU_FileInfo));

    dir->ignore_dots = ignore_dots;
    if (dir->fileinfo == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo->filename = NULL;
    dir->fileinfo->filenameW = NULL;

    wchar_t *fmtW = (wchar_t*) SDL_malloc((dirlen+3)*sizeof(wchar_t));
    wcscpy(fmtW, dirname);
    fmtW[dirlen] = L'\\';
    fmtW[dirlen + 1] = L'*';
    fmtW[dirlen + 2] = L'\0';

    char *fmt = (char*) SDL_malloc(sizeof(char) * (dirlen + 3));
    wcstombs(fmt, fmtW, dirlen+3);

    dir->handle = FindFirstFileA(fmt, &da);
    dir->handleW = FindFirstFileW(fmtW, &dw);

    SDL_free(fmt);
    SDL_free(fmtW);

    if (!dir->handle || !dir->handleW) {
        SDL_free(dir->fileinfo);
        SDL_free(dir);
        SDLU_ExitError("could not open directory", NULL);
    }

    if (ignore_dots && (!SDL_strcmp(da.cFileName, ".") || !SDL_strcmp(da.cFileName, ".."))) {
        dir->read_first = SDL_TRUE;
    }
    else {
        dir->read_first = SDL_FALSE;
        dir->fileinfo->filename = SDL_strdup(da.cFileName);
        dir->fileinfo->filenameW = _wcsdup(dw.cFileName);
        dir->fileinfo->filetype = WIN_GetFileType(dw.cFileName);
    }

    return dir;
}

SDLU_FileInfo*
WIN_NextFile(SDLU_Directory *dir)
{
    WIN32_FIND_DATAA da;
    WIN32_FIND_DATAW dw;

    if (dir == NULL)
        SDLU_ExitError("invalid parameter 'dir'", NULL);

    if (dir->read_first == SDL_TRUE) {
        dir->read_first = SDL_FALSE;

        return dir->fileinfo;
    }

    if (dir->fileinfo->filename) {
        SDL_free(dir->fileinfo->filename);
        free(dir->fileinfo->filenameW);
        dir->fileinfo->filename = NULL;
        dir->fileinfo->filenameW = NULL;
    }

    if (FindNextFileA(dir->handle, &da) && FindNextFileW(dir->handleW, &dw)) {

        if (dir->ignore_dots && (!SDL_strcmp(da.cFileName, ".") || !SDL_strcmp(da.cFileName, "..")))
            return WIN_NextFile(dir);

        dir->fileinfo->filename = SDL_strdup(da.cFileName);
        dir->fileinfo->filenameW = _wcsdup(dw.cFileName);
        dir->fileinfo->filetype = WIN_GetFileType(dw.cFileName);

        return dir->fileinfo;
    }

    return NULL;
}

void
WIN_CloseDirectory(SDLU_Directory* dir)
{
    if (dir == NULL)
        return;

    FindClose(dir->handle);
    FindClose(dir->handleW);
    if (dir->fileinfo->filename) {
        SDL_free(dir->fileinfo->filename);
        free(dir->fileinfo->filenameW);
    }

    SDL_free(dir->fileinfo);
    SDL_free(dir);
}

#endif /* FILESYSTEM_WINDOWS */
