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

#include "SDLU.h"

#define FILEDIALOG_DUMMY
#define UNUSED(x) (void)(x);

#if defined(FILEDIALOG_GTK)
# include "SDLU_filedialog_gtk_c.h"
#endif

#if defined(FILEDIALOG_WINDOWS)
# include "SDLU_filedialog_windows_c.h"
#endif

#if defined(FILEDIALOG_COCOA)
# include "SDLU_filedialog_cocoa_m.h"
#endif

const char*
SDLU_FileDialog(const char* title, Uint32 mode)
{
    /* call the appropriate native dialog */
#if defined(FILEDIALOG_WINDOWS)
    return WIN_FileDialog(title, mode);
#elif defined(FILEDIALOG_GTK)
    return GTK_FileDialog(title, mode);
#elif defined(FILEDIALOG_COCOA)
    return COCOA_FileDialog(title, mode);
#else
    return NULL;
#endif
}

void
SDLU_FreeFileDialogFilename(char* filename)
{
#if defined(FILEDIALOG_WINDOWS)
    WIN_FreeFileDialogFilename(filename);
#elif defined(FILEDIALOG_GTK)
    GTK_FreeFileDialogFilename(filename);
#elif defined(FILEDIALOG_COCOA)
    COCOA_FreeFileDialogFilename(filename);
#else
    UNUSED(filename);
#endif
}

const wchar_t*
SDLU_FileDialogW(const wchar_t* title, Uint32 mode)
{
    /* call the appropriate native dialog */
#if defined(FILEDIALOG_WINDOWS)
    return WIN_FileDialogW(title, mode);
#elif defined(FILEDIALOG_GTK)
    return GTK_FileDialogW(title, mode);
#elif defined(FILEDIALOG_COCOA)
    return COCOA_FileDialogW(title, mode);
#else
    return NULL;
#endif
}

void
SDLU_FreeFileDialogFilenameW(wchar_t* filename)
{
#if defined(FILEDIALOG_WINDOWS)
    WIN_FreeFileDialogFilenameW(filename);
#elif defined(FILEDIALOG_GTK)
    GTK_FreeFileDialogFilenameW(filename);
#elif defined(FILEDIALOG_COCOA)
    COCOA_FreeFileDialogFilenameW(filename);
#else
    UNUSED(filename);
#endif
}

