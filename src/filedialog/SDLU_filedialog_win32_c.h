#ifndef SDLU_FILEDIALOG_WIN32_C_H
#define SDLU_FILEDIALOG_WIN32_C_H

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* WIN_FileDialog(const char*, Uint32);
void WIN_FreeFileDialogFilename(char*);

#ifdef __cplusplus
}
#endif
