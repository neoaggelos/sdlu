#include "SDLU.h"

#if defined( FILESYSTEM_WIN32 )
# include "SDLU_filesystem_windows_c.h"
#elif defined( FILESYSTEM_DIRENT )
# include "SDLU_filesystem_dirent_c.h"
#else
# error("What happened")
#endif

#include <string.h>
#include <wchar.h>

static SDL_bool
string_endsin(const char* str, const char* end)
{
    size_t i;
    size_t startpos = SDL_strlen(str) - SDL_strlen(end);

    for (i = 0; i < SDL_strlen(end); i++)
        if (str[startpos + i] != end[i]) return SDL_FALSE;

    return SDL_TRUE;
}

static SDL_bool
wstring_endsin(const wchar_t* str, const wchar_t* end)
{
    size_t i;
    size_t startpos = wcslen(str) - wcslen(end);

    for (i = 0; i < wcslen(end); i++)
        if (str[startpos + i] != end[i]) return SDL_FALSE;

    return SDL_TRUE;
}

SDLU_Directory *
SDLU_OpenDirectory(const char* dirname, SDL_bool ignore_dots)
{
#if defined( FILESYSTEM_WIN32 )
    return WIN_OpenDirectory(dirname, ignore_dots);
#elif defined( FILESYSTEM_DIRENT )
    return DIR_OpenDirectory(dirname, ignore_dots);
#endif
}

SDLU_Directory *
SDLU_OpenDirectoryW(const wchar_t* dirname, SDL_bool ignore_dots)
{
#if defined( FILESYSTEM_WIN32 )
    return WIN_OpenDirectoryW(dirname, ignore_dots);
#elif defined( FILESYSTEM_DIRENT )
    return DIR_OpenDirectoryW(dirname, ignore_dots);
#endif
}

SDLU_FileInfo*
SDLU_NextFile(SDLU_Directory *dir)
{
#if defined( FILESYSTEM_WIN32 )
    return WIN_NextFile(dir);
#elif defined( FILESYSTEM_DIRENT )
    return DIR_NextFile(dir);
#endif
}

SDLU_FileInfo*
SDLU_NextFileWithExtension(SDLU_Directory* dir, const char* ext)
{
    SDLU_FileInfo *info;

    while ((info = SDLU_NextFile(dir)) && !string_endsin(info->filename, ext))
        ;

    return info;
}

SDLU_FileInfo*
SDLU_NextFileWithExtensionW(SDLU_Directory* dir, const wchar_t* ext)
{
    SDLU_FileInfo *info;

    while ((info = SDLU_NextFile(dir)) && !wstring_endsin(info->filenameW, ext))
        ;

    return info;
}

void
SDLU_CloseDirectory(SDLU_Directory *dir)
{
#if defined( FILESYSTEM_WIN32 )
    WIN_CloseDirectory(dir);
#elif defined( FILESYSTEM_DIRENT )
    DIR_CloseDirectory(dir);
#endif
}
