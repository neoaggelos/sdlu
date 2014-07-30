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

/**
 *  \file SDLU_filedialog.h
 *
 *  \brief The file dialog API
 */

#ifndef SDLU_FILEDIALOG_H
#define SDLU_FILEDIALOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL.h"
#include "begin_code.h"

/**
 *  \name SDLU_FILEDIALOG_FLAGS
 *
 *  \brief These flags can be passed to SDLU_FileDialog() to set its behaviour
 */
/*@{@*/
#define SDLU_FILEDIALOG_OPEN                0x01
#define SDLU_FILEDIALOG_SAVE                0x02
#define SDLU_FILEDIALOG_OPENDIR             0x04
/*@}@*/

/**
 *  \brief Shows a simple file chooser dialog
 *
 *  The returned pointer should be freed with SDLU_FreeFileDialogFilename()
 *
 *  \param title Window title
 *  \param mode One or more SDLU_FILEDIALOG_FLAGS
 *
 *  \return The file selected by the user on success, NULL otherwise
 */
extern DECLSPEC const char* SDLCALL SDLU_FileDialog(
        const char* title,
        Uint32 mode
);

/**
 *  \brief Free a pointer returned by SDLU_FileDialog()
 */
extern DECLSPEC void SDLCALL SDLU_FreeFileDialogFilename(char* filename);

#include "close_code.h"

#ifdef __cplusplus
}
#endif

#endif /* SDLU_FILEDIALOG_H */
