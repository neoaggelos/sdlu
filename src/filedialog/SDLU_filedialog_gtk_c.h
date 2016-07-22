
#ifndef SDLU_FILEDIALOG_GTK_C_H
#define SDLU_FILEDIALOG_GTK_C_H

#include "SDL.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* GTK_FileDialog(const char*, Uint32);
void GTK_FreeFileDialogFilename(char*);

const wchar_t* GTK_FileDialogW(const wchar_t*, Uint32);
void GTK_FreeFileDialogFilenameW(wchar_t*);

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILEDIALOG_GTK_C_H */
