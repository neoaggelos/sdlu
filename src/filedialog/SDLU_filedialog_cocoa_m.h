#ifndef SDLU_FILEDIALOG_COCOA_M_H
#define SDLU_FILEDIALOG_COCOA_M_H

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* COCOA_FileDialog(const char*, Uint32);
void COCOA_FreeFileDialogFilename(char*);

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILEDIALOG_COCOA_M_H */
