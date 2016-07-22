#ifndef SDLU_FILEDIALOG_WIN32_C_H
#define SDLU_FILEDIALOG_WIN32_C_H

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* WIN_FileDialog(const char*, Uint32);
void WIN_FreeFileDialogFilename(char*);

const wchar_t* WIN_FileDialog(const wchar_t*, Uint32);
void WIN_FreeFileDialogFilenamew(wchar_t*);

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILEDIALOG_WIN32_C_H */
