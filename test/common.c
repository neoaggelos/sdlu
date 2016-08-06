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

#include "SDL.h"
#include "common.h"

#ifdef DATA_DIR

char* GetImagePath(const char* fname)
{
    const char* basePath, *append;
    char* path;
    size_t sz;

    basePath = DATA_DIR;
#ifdef __WIN32__
    append = "\\";
#else
    append = "/";
#endif
    sz = SDL_strlen(basePath) + SDL_strlen(append) + SDL_strlen(fname);
    path = (char*)SDL_malloc(sizeof(char) * (sz+2));
    SDL_snprintf(path, sz+1, "%s%s%s", basePath, append, fname);

    return path;
}

#else /* DATA_DIR */

#ifdef __ANDROID__
char* GetImagePath(const char* fname)
{
    /*
     * on Android, we consider that images are stored in 'assets/<image>'
     * so nothing special is required
     */
    return (char*)fname;
}
#else

#ifdef _SDL_filesystem_h

char* GetImagePath(const char* fname)
{
    const char* basePath, *append;
    char* path;
    size_t sz;

    basePath = SDL_GetBasePath();
    if (!basePath) basePath = "";
#ifdef __WIN32__
    append = "..\\data\\";
#else
    append = "../data/";
#endif
    sz = SDL_strlen(basePath) + SDL_strlen(append) + SDL_strlen(fname);
    path = (char*)SDL_malloc(sizeof(char) * (sz+2));
    SDL_snprintf(path,sz+1, "%s%s%s", basePath, append, fname);

    return path;
}

#else

#define SDLU_MAXLEN 1024

int SDLU_test_vasprintf(char** s, const char* format, va_list arg);
char* SDLU_test_format(const char* format, ...);

int
SDLU_test_vasprintf(char** s, const char* format, va_list arg)
{
    char tmp[SDLU_MAXLEN];
    size_t len;

    SDL_vsnprintf(tmp, SDLU_MAXLEN-1, format, arg);
    len = SDL_strlen(tmp) + 1;

    *s = (char*)SDL_malloc(len * sizeof(char));

    SDL_memcpy(*s, tmp, len);
    return len;
}

char*
SDLU_test_format(const char* format, ...)
{
    char* ret;
    va_list arg;

    va_start(arg, format);
    SDLU_test_vasprintf(&ret, format, arg);
    va_end(arg);

    return ret;
}

/* returns 1 if 'path' is a valid file */
int SDLU_FileExists(const char* path)
{
    int result = 0;
    SDL_RWops * rwops = SDL_RWFromFile(path, "r");
    if (rwops) {
        rwops->close(rwops);
        result = 1;
    }
    return result;
}

/* 
 * The SDL FileSystem API was added late, so it may be missing
 * Handle this by checking if file exists
 */
char* GetImagePath(const char* fname)
{
#ifdef __WIN32__
    const char* path = SDLU_test_format("..\\data\\%s", fname);
    SDL_Log("No Filesystem API, will manually check location\n");
    if (SDLU_FileExists(path)) {
        return (char*)path;
    } else {
        return SDLU_test_format("data\\%s", fname);
    }
#else
    const char* path = SDLU_test_format("../data/%s", fname);
    SDL_Log("No Filesystem API, will manually check location\n");
    if (SDLU_FileExists(path)) {
        return (char*)path;
    } else {
        return SDLU_test_format("data/%s", fname);
    }
#endif
}

#endif /* _SDL_filesystem_h */

#endif /* __ANDROID__ */

#endif /* DATA_DIR */
