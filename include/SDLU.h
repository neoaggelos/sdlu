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
 *  \file SDLU.h
 *
 *  \brief Main header of the SDL Utility library.
 */

/**
 *  \mainpage The SDL Utility Library (SDLU)
 *
 *
 *  The SDL Utility Library
 *  Copyright (c) 2014 Aggelos Kolaitis <neoaggelos@gmail.com>
 *  
 *  http://sdlu.bitbucket.org
 *  
 *  The SDL Utility Library (SDLU) is a cross-platform development library that
 *  provides APIs to make development of SDL2 applications faster and easier.
 *  
 *  SDLU officially supports Windows, Linux, Mac OS X, iOS and Android.  There is
 *  also expiremental support for the Raspberry Pi.
 *  
 *  SDLU is written in C, but can be natively used in C++.
 *  
 *  It is distributed under the terms of the zlib license, see COPYING.
 *  For other software and/or source code included in this distribution,
 *  see "extras/COPYING.name".
 *  
 *  For questions, suggestions or thoughts email me at "neoaggelos@gmail.com"
 */

#ifndef SDLU_H
#define SDLU_H

/** SDLU Version **/
#define SDLU_VERSION_MAJOR 2
#define SDLU_VERSION_MINOR 1
#define SDLU_VERSION_PATCHLEVEL 1

#define SDLU_VERSION_ATLEAST(major,minor,patchlevel)                        \
    (SDLU_VERSION_MAJOR > major) ||                                         \
    ((SDLU_VERSION_MAJOR == (major)) && (SDLU_VERSION_MINOR > (minor)) ||   \
    ((SDLU_VERSOIN_MAJOR == (major)) && (SDLU_VERIONS_MINOR == (minor) &&   \
        (SDLU_VERSION_PATCHLEVEL >= (patchlevel)))

/* Use SDL for reporting errors */
#define SDLU_SetError SDL_SetError
#define SDLU_GetError SDL_GetError

#include "SDLU_config.h"

/* Basic SDLU library */
#include "SDLU_button.h"
#include "SDLU_collide.h"
#include "SDLU_combobox.h"
#include "SDLU_create.h"
#include "SDLU_defs.h"
#include "SDLU_features.h"
#include "SDLU_filedialog.h"
#include "SDLU_fps.h"
#include "SDLU_hints.h"
#include "SDLU_ini.h"
#include "SDLU_math.h"
#include "SDLU_pixels.h"
#include "SDLU_render.h"
#include "SDLU_sprite.h"
#include "SDLU_text.h"
#include "SDLU_turtle.h"

/* Optional Features */
#include "SDLU_cxx.h"
#include "SDLU_opengl.h"

#endif /* SDLU_H */
