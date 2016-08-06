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

/**
 *  \file SDLU_hints.h
 *
 *  \brief Hints that control the behaviour of the SDL Utility library. Use
 *  the SDL_SetHint/GetHint functions to control them.
 *
 *  \note These hints play essential role to how applications using them work.
 *  For that reason, NEVER control them via environment variables. The
 *  applications that use them should only Set/Get these via appropriate calls
 *  to SDL_GetHint/SetHint
 */

#ifndef SDLU_HINTS_H
#define SDLU_HINTS_H
/**
 *  \brief Controls whether button events are sent to the event queue or not.
 *
 *  Applications that do not use the event queue for checking button events
 *  (press, hover, release and lost focus), should disable this for better
 *  performance.
 *
 *  Possible values:
 *  "1": Push button events in the event queue. This is the default.
 *  "0": Do not send button events.
 */
#define SDLU_HINT_BUTTON_PUSH_EVENTS "SDLU_BUTTON_PUSH_EVENTS"

/**
 *  \brief Controls whether warnings are printed when a library call fails
 *
 *  Possible values:
 *  "0": Do not print warnings. This is the default
 *  "1": Print warnings. Can be used for debug purposes
 */
#define SDLU_HINT_LOG_WARNINGS "SDLU_LOG_WARNINGS"

/**
 *  \brief Controls if SDLU_GL_LoadTexture() adds padding to NPOT textures
 *
 *  Possible values:
 *  "always"  : Always add padding, even if the OpenGL implementation supports
 *              NPOT textures. This is the safest option.
 *  "check"   : Add padding unless NPOT textures are supported by extension
 *              ("GL_ARB_texture_non_power_of_two" or "GL_OES_texture_npot").
 *              This is the default option.
 *  "never"   : Never add padding, assuming that the OpenGL implementation
 *              can handle NPOT textures. Under normal circumstances, and to
 *              ensure code portability, you should avoid this.
 */
#define SDLU_HINT_GL_TEXTURE_ADD_PADDING "SDLU_GL_TEXTURE_ADD_PADDING"

#endif /* SDLU_HINTS_H */
