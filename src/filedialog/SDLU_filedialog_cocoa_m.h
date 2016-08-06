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
