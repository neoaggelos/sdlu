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
 *  \file SDLU_sprite.h
 *
 *  \brief Defines functions to manipulate sprites
 */

#ifndef SDLU_SPRITE_H
#define SDLU_SPRITE_H

#include "SDLU_defs.h"
#include "SDL.h"

#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Create a new sprite
 *
 *  \param renderer The associated renderer
 *
 *  \param texture The texture data. Should contain every frame of the sprite in
 *  one row separated at columns of the same width.
 *
 *  The *format* of the texture data should be like this:
 *
 *       _______________________________________________________________
 *      |               |               |               |               |
 *      |               |               |               |               |
 *      |    frame 1    |    frame 2    |    frame 3    |    frame 4    |
 *      |               |               |               |               |
 *      |_______________|_______________|_______________|_______________|
 *       \____  w  ____/ \____  w  ____/ \____  w  ____/ \____  w  ____/
 *
 *  \param frames The number of the frames of the sprite
 *
 *  \return The new sprite on success, NULL on error
 *
 *  \sa SDLU_SetSpriteFrameMode()
 */
extern DECLSPEC SDLU_Sprite* SDLCALL SDLU_CreateSprite(
        SDL_Renderer*   renderer,
        SDL_Texture*    texture,
        int             frames
);

/**
 *  \brief Create a sprite from a BMP file loaded as an SDL_RWops
 *
 *  This function is just an alias for SDLU_CreateSprite(), that will load the
 *  image data from an rwops [image must be in BMP format].
 *
 *  \param renderer The associated renderer
 *  \param rwops The rwops where the image has been loaded
 *  \param freesrc Whether to close the rwops after reading
 *  \param frames The number of the frames of the sprite
 *
 *  \return The new sprite on success, NULL on error
 */
extern DECLSPEC SDLU_Sprite* SDLCALL SDLU_CreateSpriteFromRW(
        SDL_Renderer* renderer,
        SDL_RWops* rwops,
        int freesrc,
        int frames
);

/**
 *  \brief Create a sprite from a BMP file
 *
 *  \param renderer The associated renderer
 *  \param file File name to load (must be a BMP file)
 *  \param frames The number of the frames of the sprite
 *
 *  \return The new sprite on success, NULL on error
 */
#define SDLU_CreateSpriteFromFile(renderer, file, frames) \
    SDLU_CreateSpriteFromRW(renderer, SDL_RWFromFile(file, "r"), 1, frames)

/**
 *  \brief Get a sprite with the given id
 *
 *  \param id The id of the sprite to query
 *
 *  \return The sprite with the desired id, NULL on error
 */
extern DECLSPEC SDLU_Sprite* SDLCALL SDLU_GetSpriteFromID(Uint32 id);

/**
 *  \brief Set the geometry of a sprite
 *
 *  \param sprite The sprite to update
 *  \param x,y (x,y) coordinates of the sprite, -1 to keep old position
 *  \param w,h width and height of the sprite, -1 to keep old size
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteGeometry(
        SDLU_Sprite* sprite,
        int x, int y,
        int w, int h
);

/**
 *  \brief Get the geometry of a sprite
 *
 *  \param sprite The sprite to query
 *  \param x,y Will be filled with the (x,y) coordinates of the sprite
 *  \param w,h Will be filled with the width and height of the sprite
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetSpriteGeometry(
        SDLU_Sprite* sprite,
        int* x, int* y,
        int* w, int* h
);

/**
 *  \name Direction macros for the sprite
 */
/*@{*/
#define SDLU_SPRITE_RIGHT 0
#define SDLU_SPRITE_DOWN 90
#define SDLU_SPRITE_LEFT 180
#define SDLU_SPRITE_UP 270
/*@}*/

/**
 *  \brief Set the direction of a sprite
 *
 *  This function will set the velocities on the x and y axis accordingly
 *
 *  \param sprite Sprite to update
 *  \param velocity The velocity of the sprite
 *  \param angle The angle of movement, 0 means parallel to the x axis
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteDirection(
        SDLU_Sprite* sprite,
        double velocity,
        double angle
);

/**
 *  \brief Get the direction of a sprite
 *
 *  Only use with SDLU_GetSpriteDirection()
 *
 *  \param sprite Sprite to query
 *  \param angle Will be filled with the sprite's direction
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetSpriteDirection(
        SDLU_Sprite* sprite,
        double* angle
);

/**
 *  \brief Set the velocity of the sprite
 *
 *  \param sprite The sprite to update
 *  \param xvel The velocity for the x axis
 *  \param yvel The velocity for the y axis
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteVelocity(
        SDLU_Sprite* sprite,
        double xvel,
        double yvel
);

/**
 *  \brief Get the velocity of a sprite
 *
 *  \param sprite The sprite to query
 *  \param xvel A pointer that will be filled with the xVel of the sprite
 *  \param yvel A pointer that will be filled with the yVel of the sprite
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetSpriteVelocity(
        SDLU_Sprite* sprite,
        double *xvel,
        double *yvel
);

/**
 *  \brief Set the frame refresh rate of the sprite.
 *
 *  The value of 'advance' means after how many application frames (screen
 *  refreshes) the frame pointer of the sprite should be updated. This is
 *  different than the number of frames.
 *
 *  Each call to SDLU_RenderSprite()
 *  increments an internal index specific to that sprite. Once that index
 *  reaches the maximum cap (which is the 'advance' parameter below), then the
 *  frame pointer of the sprite gets updated.
 *
 *  This function can be very useful, since if the frame pointer of a sprite
 *  got updated after every application frame, then we would either need a huge
 *  number of frames, thus loads of image data, or a very slow application
 *  framerate, which are both bad for an application.
 *
 *  Sadly, the naming of this function is not ideal, but hopefully this
 *  documentation helped you understand its importance.
 *
 *  \param sprite Sprite to update
 *  \param advance Advance value, smaller value means faster updates
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteAdvance(
        SDLU_Sprite* sprite,
        int advance
);

/**
 *  \brief Get the frame refresh rate of the sprite
 *
 *  \param sprite Sprite to query
 *  \param advance Will be filled with the refresh rate of the sprite
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetSpriteAdvance(
        SDLU_Sprite* sprite,
        int *advance
);

/**
 *  \brief Change the sprite map
 *
 *  Having 'sprite maps' is helpful for sprites that contain two or more
 *  'modes'. For example, take the main character of 2D-Platform game. Quite
 *  possibly, the character has a different set of frames for running, walking,
 *  hitting enemies, and possibly losing.
 *
 *  That means that we cannot have all these images in a series, that would mess
 *  things up. That's why sprite maps are needed. A sprite map is nothing more
 *  than an SDL_Rect describing where the frames are located in the sprite image
 *  data.
 *
 *  \param sprite Sprite to update
 *  \param map The new sprite map [NULL means the whole texture]
 *  \param frames The number of frames
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteMap(
        SDLU_Sprite* sprite,
        SDL_Rect* map,
        int frames
);

/**
 *  \brief Get the sprite map
 *
 *  \param sprite Sprite to query
 *  \param map Will be filled with the sprite's active map
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetSpriteMap(
        SDLU_Sprite* sprite,
        SDL_Rect* map
);

/**
 *  \brief Indicates how the frames in a sprite are formatted in the image data.
 *
 *  If the frames are in a single row (default), then you should pass
 *  SDLU_HORIZONTAL. If they are in a single column, you should pass
 *  SDLU_VERTICAL.
 *
 *  \param sprite Sprite to update
 *  \param mode SDLU_VERTICAL or SDLU_HORIZONTAL
 *
 *  \return 0 on success -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteFrameMode(
        SDLU_Sprite* sprite,
        int mode
);

/**
 *  \brief Query how the frames are formatted in the sprite image data.
 *
 *  \param sprite Sprite to query
 *
 *  \return SDLU_VERTICAL or SDLU_HORIZONTAL on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_GetSpriteFrameMode(SDLU_Sprite* sprite);

/**
 *  \brief Set whether the sprite is renderered rotated or not
 *
 *  \param sprite sprite to update
 *  \param draw_rotated 1 to enable rendering the sprite rotated, 0 to disable,
 *  -1 to query the current state
 *
 *  \note The rotation of the sprite is considered to be equal to the direction
 *  of the sprite, see SDLU_SetSpriteDirection()
 *
 *  \return 0 on success, -1 on error. If draw_rotated is '-1', the function
 *  returns 1 if the sprite is being drawn rotated, 0 otherwise.
 */
extern DECLSPEC int SDLCALL SDLU_SpriteDrawRotated(
        SDLU_Sprite* sprite,
        int draw_rotated
);

/**
 *  \name Functions to set custom sprite functions
 */
/*@{*/

/**
 *  \brief Set a custom render function for a sprite
 *
 *  The render function takes care of rendering the sprite on screen and also
 *  update its current frame when needed.
 *
 *  \param sprite Sprite to update
 *  \param render New render function of the sprite, NULL to reset
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteRenderFunc(
        SDLU_Sprite* sprite,
        int (*render)(SDLU_Sprite*)
);

/**
 *  \brief Set a custom update function for a sprite
 *
 *  The update function is completely user-defined, you can use it for whatever
 *  you want.
 *
 *  \param sprite Sprite to update
 *  \param update New update function of the sprite, NULL to reset
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteUpdateFunc(
        SDLU_Sprite* sprite,
        int (*update)(SDLU_Sprite*)
);

/**
 *  \brief Set a custom move function for a sprite
 *
 *  The move function takes care of moving the sprite
 *
 *  \param sprite Sprite to update
 *  \param move New move function of the sprite, NULL to reset
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetSpriteMoveFunc(
        SDLU_Sprite* sprite,
        int (*move)(SDLU_Sprite*)
);
/*@}*/

/**
 *  \name Easier execution of the sprite functions
 */
/*@{*/
/**
 * Render the sprite.
 */
#define SDLU_RenderSprite(sprite) sprite->render(sprite)
/**
 * User-defined update function.
 */
#define SDLU_UpdateSprite(sprite) sprite->update(sprite)
/**
 * Function to move the sprite and update the current 'frame'.
 */
#define SDLU_MoveSprite(sprite)   sprite->move  (sprite)
/*@}*/

/**
 *  \brief Pause or unpause a sprite
 *
 *  \param sprite The sprite to change
 *  \param pause 0 to unpause the sprite, 1 to pause it, -1 to query the
 *  current state
 *
 *  \return 0 on success, -1 on error. if *pause* is -1, then the function will
 *  return 1 if the sprite is paused, 0 otherwise.
 */
extern DECLSPEC int SDLCALL SDLU_PauseSprite(
        SDLU_Sprite* sprite,
        int pause
);

/**
 *  \brief Get the source rect of the current frame.
 *
 *  This function can be used to calculate the rect of the current sprite frame
 *  pointer.
 *
 *  \param sprite The sprite to use
 *
 *  \return The rect of the current frame, or an empty {0,0,0,0} rect otherwise
 */
extern DECLSPEC SDL_Rect SDLCALL SDLU_GetSpriteSourceRect(SDLU_Sprite* sprite);

/**
 *  \brief Add userdata to a sprite
 *
 *  \param sprite sprite to add the userdata to
 *  \param key key with which the data will be stored/referenced
 *  \param data The data to store, NULL to delete the entry
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_GetSpriteData()
 *  \sa SDLU_DelSpriteData()
 */
extern DECLSPEC int SDLCALL SDLU_AddSpriteData(
        SDLU_Sprite* sprite,
        const char* key,
        void *data
);

/**
 *  \brief Get previously stored userdata from a sprite
 *
 *  \param sprite sprite to query
 *  \param key the key with which the data was stored
 *
 *  \return the stored userdata on success, -1 on error
 *
 *  \sa SDLU_AddSpriteData()
 *  \sa SDLU_DelSpriteData()
 */
extern DECLSPEC void* SDLCALL SDLU_GetSpriteData(
        SDLU_Sprite* sprite,
        const char* key
);

/**
 *  \brief Delete previously stored userdata from a sprite
 *
 *  \param sprite sprite that contains the userdata
 *  \param key the key with which the data was stored
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDLU_AddSpriteData()
 *  \sa SDLU_GetSpriteData()
 */
extern DECLSPEC int SDLCALL SDLU_DelSpriteData(
        SDLU_Sprite* sprite,
        const char* key
);

/**
 *  \brief Destroy a sprite
 *
 *  \param sprite Sprite to destroy
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_DestroySprite(SDLU_Sprite *sprite);

#ifdef __cplusplus
}
#endif

#include "close_code.h"
#endif /* SDLU_SPRITE_H */
