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

/*
 * testfiledialog: A test program for the SDL utility library
 */

/*
 * Showing a simple file dialog box
 */

#include "SDLU.h"
#include "common.h"
#include <stdlib.h>

#ifdef SDL_MAIN_WANTED
int SDL_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* filename;
    char msg[512];

    filename = SDLU_FileDialog("Choose File", SDLU_FILEDIALOG_OPEN);

    SDL_snprintf(msg, 511, "File Chosen:\n%s", filename);
    SDLU_FreeFileDialogFilename(filename);
    SDL_Delay(1000);
    SDLU_Message(msg);

    exit(0);
}
