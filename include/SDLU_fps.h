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
 *  \file SDLU_fps.h
 *
 *  \brief Defines functions for capping the framerate
 */

#ifndef SDLU_FPS_H
#define SDLU_FPS_H

#include "SDL.h"
#include "begin_code.h"

/**
 *  \brief The default framerate used by SDLU_FPS_Init()
 */
#define SDLU_DEFAULT_FRAMERATE  60

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Initialize the framerate counter.
 *
 *  \param framerate the desired framerate. It can be any integer value.
 *  If it's <= 0, the value of SDLU_DEFAULT_FRAMERATE (60) is chosen.
 */
extern DECLSPEC void SDLCALL SDLU_FPS_Init(int framerate);

/**
 *  \brief Start the framerate counter.
 *
 *  \note MUST be called first in your main loop, or bad things will happen.
 *
 *  \sa SDLU_FPS_Cap()
 */
extern DECLSPEC void SDLCALL SDLU_FPS_Start(void);

/**
 *  \brief Delays the required amount of time to cap the framerate desired.
 *
 *  \note MUST be the last thing of your main loop or VERY BAD things will
 *  happen.
 *
 *  \sa SDLU_FPS_ToggleCap()
 *  \sa SDLU_FPS_Start()
 */
extern DECLSPEC void SDLCALL SDLU_FPS_Cap(void);

/**
 *  \brief Toggles the option to cap the framerate or not.
 *
 *  \sa SDLU_FPS_Cap()
 *  \sa SDLU_FPS_SetCap()
 */
extern DECLSPEC void SDLCALL SDLU_FPS_ToggleCap(void);

/**
 *  \brief Enable/disable framerate capping
 *
 *  \param enable 0 to disable capping the framerate, 1 or any other value to
 *  enable it
 *
 *  \sa SDLU_FPS_ToggleCap()
 *  \sa SDLU_FPS_Cap()
 */
extern DECLSPEC void SDLCALL SDLU_FPS_SetCap(int enable);

/**
 *  \brief Get the desired framerate (the one that was given at SDLU_FPS_Init).
 *
 *  \return the framerate given in SDLU_FPS_Init(), -1 on error.
 *
 *  \sa SDLU_FPS_GetRealFramerate()
 */
extern DECLSPEC int SDLCALL SDLU_FPS_GetFramerate(void);

/**
 *  \brief Get the actual framerate ( calculated by SDLU_FPS_Cap() )
 *
 *  \sa SDLU_FPS_GetFramerate()
 */
extern DECLSPEC int SDLCALL SDLU_FPS_GetRealFramerate(void);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_FPS_H */
