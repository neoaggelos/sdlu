
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
        return SDLU_REGULAR_FILE;
    }
    else if (st.st_mode & S_IFREG) {
        return SDLU_REGULAR_FILE;
    }
    else if (st.st_mode & S_IFDIR) {
        return SDLU_DIRECTORY;
    } else {
        return SDLU_REGULAR_FILE;
    }
}

SDLU_Directory *
WIN_OpenDirectory(const char *dirname, SDL_bool ignore_dots)
{
    WIN32_FIND_DATAA da;
    WIN32_FIND_DATAW dw;
    size_t dirlen = SDL_strlen(dirname);

    SDLU_Directory *dir = SDLU_malloc(SDLU_Directory);
    if (dir == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo = SDLU_malloc(SDLU_FileInfo);

    dir->ignore_dots = ignore_dots;
    if (dir->fileinfo == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo->filename = NULL;
    dir->fileinfo->filenameW = NULL;

    char *fmt = SDLU_malloc2(char, dirlen + 3);
    strcpy(fmt, dirname);
    fmt[dirlen] = '\\';
    fmt[dirlen + 1] = '*';
    fmt[dirlen + 2] = '\0';

    wchar_t *fmtW = SDLU_malloc2(wchar_t, dirlen + 3);
    mbstowcs(fmtW, fmt, dirlen+3);

    dir->handle = FindFirstFileA(fmt, &da);
    dir->handleW = FindFirstFileW(fmtW, &dw);

    SDL_free(fmt);
    SDL_free(fmtW);

    if (!dir->handle || !dir->handleW) {
        SDLU_free(dir->fileinfo);
        SDLU_free(dir);
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

    SDLU_Directory *dir = SDLU_malloc(SDLU_Directory);
    if (dir == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo = SDLU_malloc(SDLU_FileInfo);

    dir->ignore_dots = ignore_dots;
    if (dir->fileinfo == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->fileinfo->filename = NULL;
    dir->fileinfo->filenameW = NULL;

    wchar_t *fmtW = SDLU_malloc2(wchar_t, dirlen + 3);
    wcscpy(fmtW, dirname);
    fmtW[dirlen] = L'\\';
    fmtW[dirlen + 1] = L'*';
    fmtW[dirlen + 2] = L'\0';

    char *fmt = SDLU_malloc2(char, dirlen + 3);
    wcstombs(fmt, fmtW, dirlen+3);

    dir->handle = FindFirstFileA(fmt, &da);
    dir->handleW = FindFirstFileW(fmtW, &dw);

    SDL_free(fmt);
    SDL_free(fmtW);

    if (!dir->handle || !dir->handleW) {
        SDLU_free(dir->fileinfo);
        SDLU_free(dir);
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
        SDLU_ExitError("invalid directory", NULL);

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