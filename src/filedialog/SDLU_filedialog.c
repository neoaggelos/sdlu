#include "SDLU.h"

#define FILEDIALOG_DUMMY
#define UNUSED(x) (void)(x);

#if defined(FILEDIALOG_GTK)
# include "SDLU_filedialog_gtk_c.h"
#endif

#if defined(FILEDIALOG_WIN32)
# include "SDLU_filedialog_win32_c.h"
#endif

#if defined(FILEDIALOG_COCOA)
# include "SDLU_filedialog_cocoa_m.h"
#endif

const char*
SDLU_FileDialog(const char* title, Uint32 mode)
{
    /* call the appropriate native dialog */
#if defined(FILEDIALOG_WIN32)
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
#if defined(FILEDIALOG_WIN32)
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
#if defined(FILEDIALOG_WIN32)
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
#if defined(FILEDIALOG_WIN32)
    WIN_FreeFileDialogFilenameW(filename);
#elif defined(FILEDIALOG_GTK)
    GTK_FreeFileDialogFilenameW(filename);
#elif defined(FILEDIALOG_COCOA)
    COCOA_FreeFileDialogFilenameW(filename);
#else
    UNUSED(filename);
#endif
}

