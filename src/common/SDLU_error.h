/*
 * The SDL Utility library
 * Copyright (c) 2014 Aggelos Kolaitis <neoaggelos@gmail.com>
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

#ifndef SDLU_ERROR_H
#define SDLU_ERROR_H

#include "SDL.h"

/*
 * When warnings are logged under Windows, do not include source, line etc
 * For some reason, Visual Studio crashes because of this
 */
#ifdef __WINDOWS__
#   define SDLU_Log_internal( str ) SDL_Log("%s\n", str)
#else
#   define SDLU_Log_internal( str ) SDL_Log("[%s:%d](%s): %s\n",SDL_strrchr(__FILE__, '/')+1,__LINE__,__FUNCTION__,str)
#endif

#define HINT_LOG_WARNINGS \
    (SDL_strcmp(SDLU_GetHint(SDLU_HINT_LOG_WARNINGS), "1") == 0)

#ifdef _DEBUG
#define SDLU_Log SDLU_Log_internal
#else
#define SDLU_Log(str) if (HINT_LOG_WARNINGS) SDLU_Log_internal(str)
#endif

#define SDLU_ExitError( err, ret ) {                                        \
    SDLU_Log(err);                                                          \
    SDLU_SetError("%s", err);                                               \
    return ret;                                                             \
}

#endif /* SDLU_ERROR_H */
