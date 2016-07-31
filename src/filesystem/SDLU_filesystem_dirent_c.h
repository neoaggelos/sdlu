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

#endif /* SDLU_FILESYSTEM_DIRENT_C_H */
