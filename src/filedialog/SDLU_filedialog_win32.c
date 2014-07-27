#ifdef FILEDIALOG_WIN32

#include "SDLU.h"
#include <windows.h>
#include <shlobj.h>

static const char*
WIN_OpenFileDialog(const char* title)
{
    OPENFILENAME ofn;
    TCHAR *buffer;
    int i;
    
    buffer = SDL_malloc(MAX_PATH * sizeof(TCHAR));

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = TEXT(title);
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = '\0';
    ofn.hwndOwner = NULL;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = TEXT("All files(*.*)\0(*.*)\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&ofn)) {
        for (i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\\') buffer[i] = '/';
        }
        return (const char*) buffer;
    }

    return NULL;
}

static const char*
WIN_SaveFileDialog(const char* title)
{
    OPENFILENAME ofn;
    TCHAR *buffer;
    int i;
    
    buffer = SDL_malloc(MAX_PATH * sizeof(TCHAR));

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = TEXT(title);
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = '\0';
    ofn.hwndOwner = NULL;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = TEXT("All files(*.*)\0(*.*)\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileName(&ofn)) {
        for (i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\\') buffer[i] = '/';
        }
        return (const char*) buffer;
    }

    return NULL;
}

static const char*
WIN_FolderFileDialog(const char* title)
{
    BROWSEINFO bif;
    TCHAR *buffer;
    int i;

    buffer = SDL_malloc(MAX_PATH * sizeof(TCHAR));

    bif.hwndOwner = NULL;
    bif.pszDisplayName = buffer;
    bif.pszDisplayName[0] = '\0';
    bif.lpszTitle = TEXT(title);

    if (SHBrowseForFolder(&bif)) {
        for (i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '\\') buffer[i] = '/';
        }
        return (const char*) buffer;
    }

    return NULL;
}

const char*
SDLU_FileDialog(const char* title, Uint32 mode)
{
    if (!mode) mode = SDLU_FILEDIALOG_OPEN;

    if (mode & SDLU_FILEDIALOG_OPEN) {
        return WIN_OpenFileDialog(title);
    } else if (mode & SDLU_FILEDIALOG_SAVE) {
        return WIN_SaveFileDialog(title);
    } else if (mode & SDLU_FILEDIALOG_OPENDIR) {
        return WIN_FolderFileDialog(title);
    } else {
        return NULL;
    }
}

#endif /* FILEDIALOG_WIN32 */
