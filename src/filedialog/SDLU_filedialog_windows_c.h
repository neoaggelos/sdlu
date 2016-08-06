#ifndef SDLU_FILEDIALOG_WINDOWS_C_H
#define SDLU_FILEDIALOG_WINDOWS_C_H

#include "SDL.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* WIN_FileDialog(const char*, Uint32);
void WIN_FreeFileDialogFilename(char*);

const wchar_t* WIN_FileDialogW(const wchar_t*, Uint32);
void WIN_FreeFileDialogFilenameW(wchar_t*);

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILEDIALOG_WINDOWS_C_H */
