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

#include "SDLU_userdata.h"
#include "SDLU.h"
#include "SDLU_common.h"

#include <stdio.h>

static SDLU_UserData *data = NULL;

int
SDLU_AddUserData(Uint32 owner_id, int origin, const char* key, void* value)
{
    SDLU_UserData* new_data;

    /** Passing NULL as value means remove this data **/
    if (value == NULL)
        return SDLU_DelUserData(owner_id, origin, key);

    new_data = (SDLU_UserData*) SDL_malloc(sizeof(SDLU_UserData));
    if (!new_data)
        SDLU_ExitError("could not allocate memory", -1);

    new_data->owner_id  = owner_id;
    new_data->origin    = origin;
    new_data->key       = key;
    new_data->value     = value;

    LL_PREPEND(data, new_data);

    return 0;
}

void*
SDLU_GetUserData(Uint32 owner_id, int origin, const char* key)
{
    SDLU_UserData *current;

    LL_FOREACH(data, current) {
        if ( (current->owner_id == owner_id)
                && (current->origin == origin)
                && (SDL_strcmp(current->key, key) == 0) ) {
            return current->value;
        }
    }
    SDLU_ExitError("invalid parameter 'key'", NULL);
}

int
SDLU_DelUserData(Uint32 owner_id, int origin, const char* key)
{
    SDLU_UserData* current;

    LL_FOREACH(data, current) {
        if ( (current->owner_id == owner_id)
                && (current->origin == origin)
                && (SDL_strcmp(current->key, key) == 0) ) {
            LL_DELETE(data, current);

            SDL_free(current);
            return 0;
        }
    }
    SDLU_ExitError("invalid parameter 'key'", -1);
}

