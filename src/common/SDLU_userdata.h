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

#include "SDL.h"

#define FROM_BUTTON 1
#define FROM_SPRITE 2

typedef struct SDLU_UserData SDLU_UserData;

struct SDLU_UserData {
    const char *key;
    void *value;

    Uint32 owner_id;
    int origin;

    SDLU_UserData* next;
};

int     SDLU_AddUserData(Uint32 owner_id, int origin, const char* key, void* value);
void*   SDLU_GetUserData(Uint32 owner_id, int origin, const char* key);
int     SDLU_DelUserData(Uint32 owner_id, int origin, const char* key);
