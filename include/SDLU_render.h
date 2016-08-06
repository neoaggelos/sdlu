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
 *  \file SDLU_render.h
 *
 *  \brief Defines functions that extend the Render API.
 */

#ifndef SDLU_RENDER_H
#define SDLU_RENDER_H

#include "SDL.h"
#include "SDLU_defs.h"
#include "SDLU_config.h"

#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \name Polygon modes, used in SDLU_RenderBegin()
 */
/*@{*/
#define SDLU_FILL        0x00000001  /**< indicates a filled polygon   **/
#define SDLU_WIRE        0x00000002  /**< indicates an outline polygon **/
/*@}*/

/**
 *  \brief Get the index of a render driver
 *
 *  \return The driver index if successful, -1 otherwise.
 */
extern DECLSPEC int SDLCALL SDLU_GetDriverIndex(const char* driver);

#define SDLU_GetD3DIndex()      SDLU_GetDriverIndex("direct3d")
#define SDLU_GetGLIndex()       SDLU_GetDriverIndex("opengl")
#define SDLU_GetGLESIndex()     SDLU_GetDriverIndex("opengles")
#define SDLU_GetGLES2Index()    SDLU_GetDriverIndex("opengles2")
#define SDLU_GetSWIndex()       SDLU_GetDriverIndex("software")

/**
 *  \brief Get the window associated with the renderer
 *
 *  \return The associated window on success, NULL on error
 */
extern DECLSPEC SDL_Window* SDLCALL SDLU_GetWindow(SDL_Renderer* renderer);

/**
 *  \brief Load a texture with a colorkey from a .bmp file
 *
 *  \param renderer The renderer to load the texture for
 *  \param fname A string containing the name of the BMP file you want to load.
 *  \param color The color key of the new texture
 *
 *  \return A new SDL_Texture or NULL on error
 *
 *  \sa SDLU_LoadTexture()
 */
extern DECLSPEC SDL_Texture* SDLCALL SDLU_LoadTextureWithColorkey(
        SDL_Renderer* renderer,
        const char* fname,
        SDL_Color color
);

/**
 *  \brief Load a texture from a .bmp file
 *
 *  \param renderer The renderer to load the texture for
 *  \param fname A string containing the name of the BMP file you want to load.
 *
 *  \return A new SDL_Texture or NULL on error
 *
 *  \sa SDLU_LoadTextureWithColorkey()
 */
extern DECLSPEC SDL_Texture* SDLCALL SDLU_LoadTexture(
        SDL_Renderer* renderer,
        const char* fname
);

/**
 *  \brief Copy a complete texture in the given position of the renderer
 *         WITHOUT scaling it.
 *
 *  \param renderer The renderer to draw
 *  \param x,y The (x,y) coordinates to render at
 *  \param texture The texture to draw
 *
 *  \return 0 on success, -1 on error.
 */
extern DECLSPEC int SDLCALL SDLU_CopyTexture(
        SDL_Renderer* renderer,
        SDL_Texture* texture,
        int x, int y
);

/**
 *  \brief Get the size of a texture (in pixels)
 *
 *  \param texture Texture to query
 *  \param w, h Will be filled with the texture's width and height
 *
 *  \return 0 on success, -1 on error.
 */
extern DECLSPEC int SDLCALL SDLU_GetTextureSize(
        SDL_Texture* texture,
        int *w,
        int *h
);

/**
 *  \brief Draws a circle on the specified renderer with the current color.
 *
 *  \param renderer The renderer to draw
 *  \param cx,cy Coordinates of the circle's center
 *  \param r Radius of the circle
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_RenderDrawCircle(
        SDL_Renderer* renderer,
        int cx, int cy,
        int r
);

/**
 *  \brief Render a rectangle with a 1-pixel border
 *
 *  \param renderer The renderer to draw
 *  \param rect The rectangle to fill with color
 *  \param outline The border color
 *  \param fill The fill color
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_RenderDrawOutlineRect(
        SDL_Renderer* renderer,
        SDL_Rect rect,
        SDL_Color outline,
        SDL_Color fill
);

/**
 * 	\brief Start recording points
 *
 * 	This is a mere initializer function. It should be used in conjuction with
 * 	SDLU_RenderSetPoints() and SDLU_RenderEnd(). They should be used like that:
 *
 *  \code
 *  // this will draw a filled rectangle at [100,100] -> [200, 200]
 * 	SDLU_RenderBegin( SDLU_FILL );
 * 	    SDLU_RenderSetPoint( 100, 100 );
 * 	    SDLU_RenderSetPoint( 100, 200 );
 * 	    SDLU_RenderSetPoint( 200, 200 );
 * 	    SDLU_RenderSetPoint( 200, 100 );
 * 	SDLU_RenderEnd( renderer );
 * 	\endcode
 *
 * 	Or, you can pass multiple points at once like this:
 *
 * 	\code
 * 	// Same as the example above, but using SDLU_RenderSetPoints()
 * 	SDL_Points points[4] = { {100, 100}, {100, 200}, {200, 200}, {200, 100} };
 * 	SDLU_RenderBegin( SDLU_FILL );
 * 	    SDLU_RenderSetPoints( points, 4 );
 * 	SDLU_RenderEnd( renderer );
 * 	\endcode
 *
 * 	\param mode SDLU_WIRE for an outline polygon, SDLU_FILL for a filled
 * 	polygon
 *
 * 	\sa SDLU_RenderSetPoint()
 * 	\sa SDLU_RenderSetPoints()
 * 	\sa SDLU_RenderEnd()
 */
extern DECLSPEC void SDLCALL SDLU_RenderBegin(int mode);

/**
 * 	\brief Set a new point
 *
 * 	\sa SDLU_RenderEnd()
 * 	\sa SDLU_RenderBegin()
 * 	\sa SDLU_RenderSetPoints()
 */
extern DECLSPEC void SDLCALL SDLU_RenderSetPoint(int x, int y);

/**
 *  \brief Set num_points new points
 *
 *  \param points Array of points
 *  \param num_points Number of points to load
 *
 *  \sa SDLU_RenderEnd()
 *  \sa SDLU_RenderBegin()
 *  \sa SDLU_RenderSetPoint()
 */
extern DECLSPEC void SDLCALL SDLU_RenderSetPoints(
        SDL_Point *points,
        int num_points
);

/**
 * 	\brief Render the polygon with the points specified with
 * 	SDLU_RenderSetPoints()
 *
 * 	\param renderer The renderer to draw
 *
 * 	\sa SDLU_RenderSetPoint()
 * 	\sa SDLU_RenderSetPoints()
 * 	\sa SDLU_RenderBegin()
 *
 * 	\return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_RenderEnd(SDL_Renderer* renderer);

/**
 *  \brief Render a filled polygon.
 *
 *  \param renderer The renderer to draw
 *  \param points Array of points
 *  \param n Number of points.
 *
 *  \return 0 on success, -1 on error.
 *
 * 	\sa SDLU_RenderSetPoint()
 * 	\sa SDLU_RenderEnd()
 * 	\sa SDLU_RenderBegin()
 * 	\sa SDLU_RenderDrawPolygon()
 */
extern DECLSPEC int SDLCALL SDLU_RenderFillPolygon(
        SDL_Renderer* renderer,
        SDL_Point* points,
        int n
);

/**
 *  \brief Render an outline polygon.
 *
 *  \param renderer The renderer to draw
 *  \param points Array of points
 *  \param n Number of points
 *
 *  \return 0 on success, -1 on error.
 *
 *  \sa SDLU_RenderFillPolygon()
 *  \sa SDLU_RenderSetPoint()
 *  \sa SDLU_RenderEnd()
 *  \sa SDLU_RenderBegin()
 */
extern DECLSPEC int SDLCALL SDLU_RenderDrawPolygon(
        SDL_Renderer* renderer,
        SDL_Point *points,
        int n
);

/**
 *  \brief Render a texture n times, each time adjusting dest according to
 *  format.
 *
 *  As for the 'format' argument, the only restriction is that when you alter
 *  one of 'x,y,w,h' the +-[amount_of_change], must have no spaces in between.
 *  'x+10' is understood, 'y+ 20' or 'x - 1' are not.
 *
 *  When you give more than one of 'x,y,w,h', between each of them you can have
 *  anything you want, see the example below.
 *
 *  Example:
 *
 *  \code
 *  // Copy 'texture' 5 times on renderer. The original destination is 'dst'
 *  // Each time, the destination rect is moved 10 pixels down (x+10) and
 *  // 40 pixels up (y-40).
 *  SDLU_RenderMultiCopy( renderer, texture, src, dst, 5, "x+10, y-40" );
 *  \endcode
 *
 *  \param renderer The renderer to draw
 *  \param texture Texture to copy
 *  \param src The source rect
 *  \param dest The original destination rect
 *  \param n Loops n times
 *  \param format How the dest rect should change every time
 *
 *  \return 0 on success, -1 on error
 *
 */
extern DECLSPEC int SDLCALL SDLU_RenderMultiCopy(
        SDL_Renderer* renderer,
        SDL_Texture* texture,
        SDL_Rect *src,
        SDL_Rect *dest,
        int n,
        const char* format
);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_RENDER_H */
