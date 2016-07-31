#include "SDLU.h"
#include "SDLU_common.h"

#include "SDLU_filesystem_dirent_c.h"

#include <wchar.h>
#include <sys/types.h>
#include <sys/stat.h>

static SDLU_FileType
DIR_GetFileType(const char *file)
{
    struct stat st;

    if (lstat(file, &st) == -1) {
        return SDLU_REGULAR_FILE;
    } else if (st.st_mode & S_IFREG) {
        return SDLU_REGULAR_FILE;
    } else if (st.st_mode & S_IFDIR) {
        return SDLU_DIRECTORY;
    } else if (st.st_mode & S_IFLNK) {
        return SDLU_SYMBOLIC_LINK;
    } else {
        return SDLU_REGULAR_FILE;
    }
}

SDLU_Directory*
DIR_OpenDirectory(const char *dirname, SDL_bool ignore_dots)
{
    SDLU_Directory *dir = SDLU_malloc(SDLU_Directory);
    if (dir == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->info = SDLU_malloc(SDLU_FileInfo);
    if (dir->info == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    dir->info->filename = NULL;
    dir->info->filenameW = NULL;

    dir->dir = opendir(dirname);
    if (dir->dir == NULL)
        SDLU_ExitError("could not open directory", NULL);

    dir->ignore_dots = ignore_dots;

    return dir;
}

SDLU_Directory*
DIR_OpenDirectoryW(const wchar_t *dirname, SDL_bool ignore_dots)
{
    char *actual;

    actual = SDLU_malloc2(char, wcslen(dirname));
    wcstombs(actual, dirname, wcslen(dirname));

    return DIR_OpenDirectory(actual, ignore_dots);
}

SDLU_FileInfo*
DIR_NextFile(SDLU_Directory *dir)
{
    struct dirent *ent = readdir(dir->dir);

    if (dir->info->filename) {
        SDL_free(dir->info->filename);
        SDL_free(dir->info->filenameW);
        dir->info->filename = NULL;
        dir->info->filenameW = NULL;
    }

    if (ent != NULL) {
        if (dir->ignore_dots && (!SDL_strcmp(ent->d_name, ".") || !SDL_strcmp(ent->d_name, "..")))
            return DIR_NextFile(dir);

        dir->info->filename = SDL_strdup(ent->d_name);

        dir->info->filenameW = SDLU_malloc2(wchar_t, SDL_strlen(dir->info->filename));
        mbstowcs(dir->info->filenameW, dir->info->filename, SDL_strlen(dir->info->filename));

        dir->info->filetype = DIR_GetFileType(ent->d_name);
        return dir->info;
    }

    return NULL;
}

void
DIR_CloseDirectory(SDLU_Directory *dir)
{
    if (dir) {
        if (dir->info->filename) SDL_free(dir->info->filename);
        if (dir->info->filenameW) SDL_free(dir->info->filenameW);
        if (dir->info) SDL_free(dir->info);

        SDL_free(dir);
    }
}

