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

#include "SDLU.h"
#include "SDLU_common.h"
#include "SDLU_userdata.h"
#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

/* PI */
#define SDLU_PI 3.14159265358979323846

/**
 * checks if two SDL_Rects are equal
 */
#define SDLU_RECTS_ARE_EQUAL(a,b)                                   \
         ((a).x == (b).x) && ((a).y == (b).y)                       \
      && ((a).w == (b).w) && ((a).h == (b).h)

int SDLU_RenderSprite_BuiltIn(SDLU_Sprite*);
int SDLU_MoveSprite_BuiltIn(SDLU_Sprite*);
int SDLU_UpdateSprite_BuiltIn(SDLU_Sprite*);

SDLU_Sprite *sprites = NULL;
Uint32 next_id = 1;

SDLU_Sprite *
SDLU_CreateSprite( SDL_Renderer *renderer, SDL_Texture *texture, int frames)
{
    SDLU_Sprite *sprite;
    int texw, texh;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", NULL);
    if (texture == NULL)
        SDLU_ExitError("invalid parameter 'texture'", NULL);
    if (frames <= 0)
        SDLU_ExitError("parameter 'frames' can't be negative", NULL);

    sprite = SDLU_malloc(SDLU_Sprite);
    if (sprite == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    sprite->id = next_id++;
    sprite->frames.max   = frames;
    sprite->frames.index = 0;

    sprite->advance.max = 1;
    sprite->advance.index = 0;

    sprite->direction = 0;
    sprite->know_direction = 0;

    sprite->xvel = 0;
    sprite->yvel = 0;
    sprite->xoffset = 0;
    sprite->yoffset = 0;

    sprite->renderer = renderer;
    sprite->data = texture;

    SDLU_GetTextureSize(texture, &texw, &texh);
    sprite->rect.w = texw / frames;
    sprite->rect.h = texh;
    sprite->rect.x = 0;
    sprite->rect.y = 0;

    sprite->update  = SDLU_UpdateSprite_BuiltIn;
    sprite->render  = SDLU_RenderSprite_BuiltIn;
    sprite->move    = SDLU_MoveSprite_BuiltIn;

    sprite->is_paused = 0;
    sprite->mode = SDLU_HORIZONTAL;

    sprite->unused = NULL;

    SDLU_SetSpriteMap(sprite, NULL, frames);

    LL_PREPEND(sprites, sprite);

    return sprite;
}

SDLU_Sprite*
SDLU_CreateSpriteFromRW(SDL_Renderer* renderer, SDL_RWops* rwops, int freesrc, int frames)
{
    SDL_Surface* temp_surface;
    SDL_Texture* texture;

    temp_surface = SDL_LoadBMP_RW(rwops, freesrc);
    texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return SDLU_CreateSprite(renderer, texture, frames);
}

int
SDLU_SetSpriteVelocity(SDLU_Sprite* sprite, double xvel, double yvel)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    sprite->xvel = xvel;
    sprite->yvel = yvel;

    return 0;
}

int
SDLU_GetSpriteVelocity(SDLU_Sprite* sprite, double* xvel, double* yvel)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (xvel) *xvel = sprite->xvel;
    if (yvel) *yvel = sprite->yvel;

    return 0;
}

int
SDLU_SetSpriteDirection(SDLU_Sprite* sprite, double velocity, double angle)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    sprite->direction = angle;
    sprite->know_direction = 1;

    /* cos() and sin() want rad */
    angle *= (SDLU_PI / 180.0);

    sprite->xvel = SDL_cos(angle) * velocity;
    sprite->yvel = SDL_sin(angle) * velocity;

    return 0;
}

int
SDLU_GetSpriteDirection(SDLU_Sprite* sprite, double* angle)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (sprite->know_direction) {
        if (angle) *angle = sprite->direction;
    } else {
        SDLU_ExitError("sprite direction unknown", -1);
    }

    return 0;
}

int
SDLU_SetSpriteGeometry(SDLU_Sprite* sprite, int x, int y, int w, int h)
{
    SDL_Rect* rect;
    int result = 0;
    int renderer_w, renderer_h;

    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    rect = &(sprite->rect);

    result |= SDL_GetRendererOutputSize(
            sprite->renderer, &renderer_w, &renderer_h
    );

    if (x != -1) rect->x = x;
    if (y != -1) rect->y = y;
    if (w != -1) rect->w = w;
    if (h != -1) rect->h = h;
    return result;
}

int
SDLU_GetSpriteGeometry(SDLU_Sprite* sprite, int *x, int *y, int *w, int *h)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (x) *x = sprite->rect.x;
    if (y) *y = sprite->rect.y;
    if (w) *w = sprite->rect.w;
    if (h) *h = sprite->rect.h;

    return 0;
}

int
SDLU_PauseSprite(SDLU_Sprite* sprite, int pause)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (pause == -1) {
        return sprite->is_paused ? 1 : 0;
    } else {
        sprite->is_paused = pause ? 1 : 0;
    }

    return 0;
}

int
SDLU_AddSpriteData( SDLU_Sprite* sprite, const char* key, void *data )
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (key == NULL)
        SDLU_ExitError("invalid parameter 'key'", -1);

    return SDLU_AddUserData(sprite->id, 1, key, data);
}

void*
SDLU_GetSpriteData( SDLU_Sprite* sprite, const char* key )
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", NULL);

    if (key == NULL)
        SDLU_ExitError("invalid parameter 'key'", NULL);

    return SDLU_GetUserData(sprite->id, 1, key);
}

int
SDLU_DelSpriteData(SDLU_Sprite* sprite, const char* key)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (key == NULL)
        SDLU_ExitError("invalid parameter 'key'", -1);

    return SDLU_DelUserData(sprite->id, 1, key);
}

int
SDLU_GetSpritePaused(SDLU_Sprite* sprite)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    return sprite->is_paused;
}

int
SDLU_SetSpriteMap(SDLU_Sprite* sprite, SDL_Rect* map, int frames)
{
    int result = 0;
    int w, h;
    SDL_Rect area;

    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (map) {
        area = *map;
    } else {
        SDLU_GetTextureSize(sprite->data, &w, &h);
        area.x = 0;
        area.y = 0;
        area.w = w;
        area.h = h;
    }

    sprite->map = area;
    sprite->frames.max = frames;
    sprite->frames.index = 0;

    return result;
}

int
SDLU_GetSpriteMap(SDLU_Sprite* sprite, SDL_Rect* map)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (map) *map = sprite->map;

    return 0;
}

int
SDLU_DestroySprite(SDLU_Sprite *sprite)
{
    if (sprite) {
        if (sprites) LL_DELETE(sprites, sprite);
        SDL_DestroyTexture(sprite->data);
        SDL_free(sprite);
        return 0;
    } else {
        SDLU_ExitError("invalid parameter 'sprite'", -1);
    }
}

int
SDLU_SetSpriteAdvance(SDLU_Sprite *sprite, int advance)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (advance <= 0)
        SDLU_ExitError("parameter 'advance' can't be negative", -1);

    sprite->advance.max = advance;
    sprite->advance.index = 0;
    return 0;
}

int
SDLU_GetSpriteAdvance(SDLU_Sprite* sprite, int *advance)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (advance) *advance = sprite->advance.max;

    return 0;
}

int
SDLU_SpriteDrawRotated(SDLU_Sprite* sprite, int draw_rotated)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (draw_rotated == -1) {
        return sprite->draw_rotated != 0;
    } else {
        sprite->draw_rotated = (draw_rotated ? 1 : 0);
    }

    return 0;
}

int
SDLU_SetSpriteFrameMode(SDLU_Sprite *sprite, int mode)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (mode == SDLU_VERTICAL || mode == SDLU_HORIZONTAL) {
        sprite->mode = mode;
    } else {
        SDLU_ExitError("parameter 'mode' is out of range", -1);
    }

    return 0;
}

int
SDLU_GetSpriteFrameMode(SDLU_Sprite* sprite)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    return sprite->mode;
}

int
SDLU_MoveSprite_BuiltIn(SDLU_Sprite *sprite)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (sprite->is_paused) {
        SDLU_Log("sprite is paused");
        return -1;
    }

    sprite->rect.x += (int)sprite->xvel;
    sprite->rect.y += (int)sprite->yvel;

    /* xoffset, yoffset hold how much the sprite is off from its on-screen
     * position
     *
     * when they get equal to or greater than one, we add their integer part to
     * the position.
     *
     * this mechanism allows to have sprites whose velocity is a double rather
     * than an integer, which is good
     */
    sprite->xoffset += sprite->xvel - (int)sprite->xvel;
    sprite->yoffset += sprite->yvel - (int)sprite->yvel;

    if (sprite->xoffset >= 1.0 || sprite->xoffset <= -1.0) {
        sprite->rect.x += (int)sprite->xoffset;
        sprite->xoffset -= (int)sprite->xoffset;
    }

    if (sprite->yoffset >= 1.0 || sprite->yoffset <= -1.0) {
        sprite->rect.y += (int)sprite->yoffset;
        sprite->yoffset -= (int)sprite->yoffset;
    }

    return 0;
}

int
SDLU_UpdateSprite_BuiltIn(SDLU_Sprite *sprite)
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (sprite->is_paused) {
        SDLU_Log("sprite is paused");
        return -1;
    }

    UNUSED(sprite);
    return 0;
}

int
SDLU_RenderSprite_BuiltIn(SDLU_Sprite *sprite)
{
    SDL_Rect srcrect;
    int result;
    double angle = 0;

    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    srcrect = SDLU_GetSpriteSourceRect(sprite);

    if (sprite->know_direction) {
        angle = (sprite->draw_rotated ? sprite->direction : 0);
    } else {
        angle = 0;
    }

    result = SDL_RenderCopyEx(sprite->renderer, sprite->data,
            &srcrect, &(sprite->rect), angle, NULL, 0);

    if (sprite->is_paused) {
        SDLU_Log("sprite is paused");
    } else {
        /**
         *  sprite->advance is a counter.
         *
         *  after rendering the sprite, the counter (index) increases by 1
         *  When it reaches the limit (max), then we refresh the sprite's frame
         */
        if (++(sprite->advance.index) >= sprite->advance.max) {
            sprite->frames.index++;
            sprite->frames.index %= sprite->frames.max;
            sprite->advance.index = 0;
        }
    }

    return result;
}

int
SDLU_SetSpriteRenderFunc(SDLU_Sprite* sprite, int (*render)(SDLU_Sprite*))
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (render) {
        sprite->render = render;
    } else {
        sprite->render = SDLU_RenderSprite_BuiltIn;
    }

    return 0;
}

int
SDLU_SetSpriteMoveFunc(SDLU_Sprite* sprite, int (*move)(SDLU_Sprite*))
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (move) {
        sprite->move = move;
    } else {
        sprite->move = SDLU_MoveSprite_BuiltIn;
    }

    return 0;
}

int
SDLU_SetSpriteUpdateFunc(SDLU_Sprite* sprite, int (*update)(SDLU_Sprite*))
{
    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", -1);

    if (update) {
        sprite->update = update;
    } else {
        sprite->update = SDLU_UpdateSprite_BuiltIn;
    }

    return 0;
}

SDLU_Sprite*
SDLU_GetSpriteFromID(Uint32 id)
{
    SDLU_Sprite* sprite;
    LL_FOREACH(sprites, sprite) {
        if (sprite->id == id) {
            return sprite;
        }
    }
    SDLU_ExitError("parameter 'id' is out of range", NULL);
}

SDL_Rect
SDLU_GetSpriteSourceRect(SDLU_Sprite* sprite)
{
    SDL_Rect rect;
    SDL_Rect *map;
    SDLU_Counter *frames;

    rect.x = rect.y = rect.w = rect.h = 0;

    if (sprite == NULL)
        SDLU_ExitError("invalid parameter 'sprite'", rect);

    map = &(sprite->map);
    frames = &(sprite->frames);

    if (sprite->mode == SDLU_HORIZONTAL) {
        rect.x = map->x + map->w * frames->index / frames->max;
        rect.y = map->y;
        rect.w = map->w / frames->max;
        rect.h = map->h;
    } else if (sprite->mode == SDLU_VERTICAL) {
        rect.x = map->x;
        rect.y = map->y + map->h * frames->index / frames->max;
        rect.w = map->w;
        rect.h = map->h / frames->max;
    } else {
        SDLU_ExitError("unknown sprite mode", rect);
    }

    return rect;
}
