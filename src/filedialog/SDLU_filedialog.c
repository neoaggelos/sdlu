#include "SDLU.h"

#define UNUSED(x) (void)(x);

const char*
SDLU_FileDialog(const char* title, Uint32 mode)
{
    /* call the appropriate native dialog */
#if defined(FILEDIALOG_WIN32)
    return WIN_FileDialog(title, mode);
#elif defined(FILEDIALOG_GTK)
    return GTK_FileDialog(title, mode);
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
#else
    UNUSED(filename);
#endif
}
