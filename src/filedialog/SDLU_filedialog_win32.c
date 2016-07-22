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

        filename = SDL_strdup(ofn.lpstrFile);
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

        filename = SDL_strdup(ofn.lpstrFile);
        return (const char*)filename;
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

        filename = SDL_strdup(buffer);
        return (const char*)filename;
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


static const wchar_t*
WIN_OpenFileDialogW(const wchar_t* title)
{
    OPENFILENAMEW ofn;
    wchar_t buffer[MAX_PATH];
    wchar_t *filename;
    unsigned int i;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = title;
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = L'\0';
    ofn.hwndOwner = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"All files(*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameW(&ofn)) {
        for (i = 0; i < SDL_wcslen(ofn.lpstrFile); i++) {
            if (ofn.lpstrFile[i] == L'\\') ofn.lpstrFile[i] = L'/';
        }

        filename = _wcsdup(ofn.lpstrFile);
        return (const wchar_t*)filename;
    }

    return NULL;
}

static const wchar_t*
WIN_SaveFileDialogW(const wchar_t* title)
{
    OPENFILENAMEW ofn;
    wchar_t buffer[MAX_PATH];
    wchar_t *filename;
    unsigned int i;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = title;
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = L'\0';
    ofn.hwndOwner = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"All files(*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileNameW(&ofn)) {
        for (i = 0; i < SDL_wcslen(ofn.lpstrFile); i++) {
            if (ofn.lpstrFile[i] == L'\\') ofn.lpstrFile[i] = L'/';
        }

        filename = _wcsdup(ofn.lpstrFile);
        return (const wchar_t*)filename;
    }

    return NULL;
}

static const wchar_t*
WIN_FolderFileDialogW(const wchar_t* title)
{
    BROWSEINFOW bif;
    wchar_t _buffer[MAX_PATH];
    LPITEMIDLIST idl;
    wchar_t *filename;
    unsigned int i;

    ZeroMemory(&bif, sizeof(bif));
    bif.hwndOwner = NULL;
    bif.pszDisplayName = _buffer;
    bif.pszDisplayName[0] = L'\0';
    bif.lpszTitle = title;

    if ((idl = SHBrowseForFolderW(&bif)) != NULL) {
        wchar_t buffer[MAX_PATH];
        SHGetPathFromIDListW(idl, buffer);

        for (i = 0; i < SDL_wcslen(buffer); i++) {
            if (buffer[i] == L'\\') buffer[i] = L'/';
        }

        filename = _wcsdup(buffer);
        return (const wchar_t*)filename;
    }

    return NULL;
}

const wchar_t*
WIN_FileDialogW(const wchar_t* title, Uint32 mode)
{
    if (!mode) mode = SDLU_FILEDIALOG_OPEN;

    if (mode & SDLU_FILEDIALOG_OPEN) {
        return WIN_OpenFileDialogW(title);
    }
    else if (mode & SDLU_FILEDIALOG_SAVE) {
        return WIN_SaveFileDialogW(title);
    }
    else if (mode & SDLU_FILEDIALOG_OPENDIR) {
        return WIN_FolderFileDialogW(title);
    }
    else {
        return NULL;
    }
}

void
WIN_FreeFileDialogFilenameW(wchar_t* filename)
{
    if (filename) free(filename);
}


#endif /* FILEDIALOG_WIN32 */
