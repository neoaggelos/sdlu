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
 *  \file SDLU_features.h
 *
 *  \brief Defines SDLU feature macros
 *
 *  Given the many changes that are made in SDLU from version to version, and
 *  since it's hard to find out if a feature (e.g. a new API, a particular
 *  function) is included, this file was added as a "compromise". This file
 *  defines macros, which, when they exist, you can be sure that the existing
 *  API exists.
 */

#ifndef SDLU_FEATURES_H
#define SDLU_FEATURES_H

/* APIs */
#define SDLU_API_BUTTON             1
#define SDLU_API_COLLISIONDETECTION 1
#define SDLU_API_COMBOBOX           1
#define SDLU_API_FRAMERATE          1
#define SDLU_API_INIHANDLER         1
#define SDLU_API_MATH               1
#define SDLU_API_OPENGL             1
#define SDLU_API_SPRITE             1
#define SDLU_API_TEXTRENDERING      1
#define SDLU_API_TURTLE             1

/* APIs that will be added in the future */
/* #define SDLU_API_FILECHOOSER        1 */
/* #define SDLU_API_LABEL              1*/
/* #define SDLU_API_MENUBAR            1*/
/* #define SDLU_API_PROGRESSBAR        1*/
/* #define SDLU_API_TEXTRENDERER       1*/

/* Functions */
#define SDLU_SET_BUTTON_STYLES  1

#endif /* SDLU_FEATURES_H */
