#ifdef FILEDIALOG_WIN32

#include "SDLU.h"
#include <windows.h>
#include <shlobj.h>

static const char*
WIN_OpenFileDialog(const char* title)
{
    OPENFILENAMEA ofn;
    char buffer[MAX_PATH];
    char *filename;
    unsigned int i;
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = title;
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = '\0';
    ofn.hwndOwner = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "All files(*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&ofn)) {
        for (i = 0; i < SDL_strlen(ofn.lpstrFile); i++) {
            if (ofn.lpstrFile[i] == '\\') ofn.lpstrFile[i] = '/';
        }

        filename = SDL_malloc((SDL_strlen(ofn.lpstrFile) + 2) * sizeof(char));
        SDL_snprintf(filename, SDL_strlen(ofn.lpstrFile) + 2, "%s", ofn.lpstrFile);

        return (const char*) filename;
    }

    return NULL;
}

static const char*
WIN_SaveFileDialog(const char* title)
{
    OPENFILENAMEA ofn;
    char buffer[MAX_PATH];
    char *filename;
    unsigned int i;
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = title;
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = '\0';
    ofn.hwndOwner = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "All files(*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileNameA(&ofn)) {
        for (i = 0; i < SDL_strlen(ofn.lpstrFile); i++) {
            if (ofn.lpstrFile[i] == '\\') ofn.lpstrFile[i] = '/';
        }

        filename = SDL_malloc((SDL_strlen(ofn.lpstrFile) + 2) * sizeof(char));
        SDL_snprintf(filename, SDL_strlen(ofn.lpstrFile) + 2, "%s", ofn.lpstrFile);

        return (const char*) filename;
    }

    return NULL;
}

static const char*
WIN_FolderFileDialog(const char* title)
{
    BROWSEINFOA bif;
    char _buffer[MAX_PATH];
    LPITEMIDLIST idl;
    char *filename;
    unsigned int i;

    ZeroMemory(&bif, sizeof(bif));
    bif.hwndOwner = NULL;
    bif.pszDisplayName = _buffer;
    bif.pszDisplayName[0] = '\0';
    bif.lpszTitle = title;

    if ((idl = SHBrowseForFolderA(&bif)) != NULL) {
        char buffer[MAX_PATH];
        SHGetPathFromIDListA(idl, buffer);

        for (i = 0; i < SDL_strlen(buffer); i++) {
            if (buffer[i] == '\\') buffer[i] = '/';
        }

        filename = SDL_malloc((SDL_strlen(buffer) + 2) * sizeof(char));
        SDL_snprintf(filename, SDL_strlen(buffer) + 2, "%s", buffer);

        return (const char*) filename;
    }

    return NULL;
}

const char*
WIN_FileDialog(const char* title, Uint32 mode)
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

void
WIN_FreeFileDialogFilename(char* filename)
{
    if (filename) SDL_free(filename);
}

#endif /* FILEDIALOG_WIN32 */
