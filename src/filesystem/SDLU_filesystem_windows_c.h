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

#endif /* SDLU_FILESYSTEM_WINDOWS_C_H */
