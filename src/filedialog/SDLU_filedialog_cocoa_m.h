#ifndef SDLU_FILEDIALOG_COCOA_M_H
#define SDLU_FILEDIALOG_COCOA_M_H

#include "SDL.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* COCOA_FileDialog(const char*, Uint32);
void COCOA_FreeFileDialogFilename(char*);

const wchar_t* COCOA_FileDialogW(const wchar_t*, Uint32);
void COCOA_FreeFileDialogFilenameW(wchar_t*);

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILEDIALOG_COCOA_M_H */
