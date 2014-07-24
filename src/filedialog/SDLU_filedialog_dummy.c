#ifdef FILEDIALOG_DUMMY

#include "SDLU.h"

#define UNUSED(var) (void)(var);

const char*
SDLU_FileDialog(const char* title, Uint32 mode)
{
    UNUSED(title);
    UNUSED(mode);
    return NULL;
}

#endif
