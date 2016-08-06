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


#include "SDLU.h"
#include "SDLU_defs.h"
#include "SDLU_render_c.h"
#include "SDLU_common.h"
#include <stdio.h>

/* Internal stuff */

/* used for polygon rendering */
static SDLU_PList *head, *node;
static Uint32 type;

/* used by SDLU_RenderPolygon */
static int SDLU_cint(const void* a, const void* b)
{
    return (*(const int* )a) - (*(const int*) b);
}

#define draw_point(x,y) \
    SDL_RenderDrawPoint(renderer, x, y);

static void
_SDLU_CirclePoints(SDL_Renderer* renderer,int cx, int cy, int x, int y)
{
    if (x==0) {
        draw_point( cx, cy+y);
        draw_point( cx, cy-y);
        draw_point( cx+y, cy);
        draw_point( cx-y, cy);
    } else if (x==y) {
        draw_point(cx+x, cy+y);
        draw_point(cx-x, cy+y);
        draw_point(cx+x, cy-y);
        draw_point(cx-x, cy-y);
    } else if (x < y) {
        draw_point( cx+x, cy+y);
        draw_point( cx-x, cy+y);
        draw_point(cx+x, cy-y);
        draw_point(cx-x, cy-y);
        draw_point(cx+y, cy+x);
        draw_point(cx-y, cy+x);
        draw_point(cx +y, cy -x);
        draw_point(cx-y, cy-x);
    }
}

/* End of internal stuff */

int
SDLU_GetDriverIndex(const char* driver)
{
    SDL_RendererInfo info;
    int id;

    for (id = 0; id < SDL_GetNumRenderDrivers(); id++) {
        SDL_GetRenderDriverInfo(id,&info);
        if (SDL_strcmp(driver,info.name) == 0)
            return id;
    }

    SDLU_Log(SDLU_format("driver '%s' not found", driver));
    return -1;
}

SDL_Window* SDLU_GetWindow(SDL_Renderer* renderer)
{
    int index;
    const int MAX_ID = 100;         /* a safe maximum id to check */

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", NULL);

    for (index = 0; index < MAX_ID; index++) {
        SDL_Window* window = SDL_GetWindowFromID(index);
        if (SDL_GetRenderer(window) == renderer) {
            return window;
        }
    }

    SDLU_ExitError("associated window not found", NULL);
#undef MAX_ID
}

int
SDLU_GetTextureSize(SDL_Texture* texture, int* w, int* h)
{
    return SDL_QueryTexture(texture,NULL,NULL,w,h);
}

int
SDLU_CopyTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
    int result = 0;
    SDL_Rect dest;
    int w, h;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    if (texture == NULL)
        SDLU_ExitError("invalid parameter 'texture'", -1);

    result |= SDLU_GetTextureSize(texture, &w, &h);

    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    result |= SDL_RenderCopy(renderer, texture, NULL, &dest);

    return result;
}

int
SDLU_RenderDrawCircle(SDL_Renderer* renderer, int cx, int cy, int r)
{
    int x = 0;
    int y = r;
    int p = ( 5- r*4)/4;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    _SDLU_CirclePoints(renderer, cx, cy,x,y);
    while(x<y) {
        x++;
        if (p < 0)
            p+=2*x+1;
        else {
            y--;
            p+=2*(x-y)+1;
        }
        _SDLU_CirclePoints(renderer, cx,cy,x,y);
    }
    return 0;
}

SDL_Texture*
SDLU_LoadTexture(SDL_Renderer* renderer, const char* fname)
{
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", NULL);

    surface = SDL_LoadBMP(fname);                       /* load image */
    if (surface == NULL)
        SDLU_ExitError("could not load BMP file", NULL);

    texture = SDL_CreateTextureFromSurface(             /* create texture */
            renderer, surface);

    SDL_FreeSurface(surface);                           /* free temp surface */

    if (texture == NULL)
        SDLU_ExitError("could not create texture", NULL);

    return texture;
}

SDL_Texture*
SDLU_LoadTextureWithColorkey(SDL_Renderer* renderer, const char* fname, SDL_Color color)
{
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    Uint32 colorkey;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", NULL);

    surface = SDL_LoadBMP(fname);                       /* load image */
    if (surface == NULL)
        SDLU_ExitError("could not load BMP file", NULL);

    colorkey = SDLU_RenderMapRGBA(renderer,
            color.r, color.g, color.b, color.a);

    if (SDL_SetColorKey(surface, 1, colorkey) == -1) {
        SDL_FreeSurface(surface);                       /* set colorkey */
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(             /* create texture */
            renderer, surface);

    SDL_FreeSurface(surface);                           /* free temp surface */

    if (texture == NULL)
        SDLU_ExitError("could not create texture", NULL);

    return texture;
}

int
SDLU_RenderDrawOutlineRect(SDL_Renderer* renderer, SDL_Rect rect,
                        SDL_Color outline, SDL_Color fill)
{
    Uint8 r, g, b, a;
    int result = 0;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    /* backup original color */
    result |= SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    /* draw outline */
    result |= SDL_SetRenderDrawColor(renderer,
            outline.r, outline.g, outline.b, outline.a);
    result |= SDL_RenderDrawRect(renderer, &rect);

    /* draw fill */
    rect.x ++ ; rect.y ++;
    rect.w -=2 ; rect.h -= 2;
    result |= SDL_SetRenderDrawColor(renderer,
            fill.r, fill.g, fill.b, fill.a);
    result |= SDL_RenderFillRect(renderer, &rect);

    /* restore original color */
    result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
    return result;
}

int
SDLU_RenderMultiCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                     SDL_Rect *src, SDL_Rect* dest, int n,
                     const char* format)
{
    int result = 0;
    int i, k;
    int dx = 0;
    int dy = 0;
    int dw = 0;
    int dh = 0;
    SDL_Rect dst;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    if (texture == NULL)
        SDLU_ExitError("invalid parameter 'texture'", -1);

    if (dest) {
        dst.x = dest->x;
        dst.y = dest->y;
        dst.w = dest->w;
        dst.h = dest->h;
    } else
        dst.x = dst.y = dst.w = dst.h = 0;

    dw = dh = dx = dy = 0;
    if (format && dest) {
        for (i = 0; i < (signed int)SDL_strlen(format); i++) {
            switch (format[i]) {
                case 'w':
                    if (format[i+1] != '+' && format[i+1] != '-')
                        break;
                    if (format[i+1] && format[i+2]) {
                        for (k = i+2; k < (signed int)SDL_strlen(format) ; k++) {
                            if (SDL_isdigit(format[k]))
                                dw = 10*dw + format[k]-'0';
                            else
                                break;
                        }
                        if (format[i+1] == '-')
                            dw = -dw;
                        i = k -1;
                    }
                    break;
                case 'h':
                    if (format[i+1] != '+' && format[i+1] != '-')
                        break;
                    if (format[i+1] && format[i+2]) {
                        for (k = i+2; k < (signed int)SDL_strlen(format) ; k++) {
                            if (SDL_isdigit(format[k]))
                                dh = 10*dh + format[k] -'0';
                            else
                                break;
                        }
                        if (format[i+1] == '-')
                            dh = -dh;
                        i = k -1;
                    }
                    break;
                case 'x':
                    if (format[i+1] != '+' && format[i+1] != '-')
                        break;
                    if (format[i+1] && format[i+2]) {
                        for (k = i+2; k < (signed int)SDL_strlen(format) ; k++) {
                            if (SDL_isdigit(format[k]))
                                dx = 10*dx + format[k] - '0';
                            else
                                break;
                        }
                        if (format[i+1] == '-')
                            dx = -dx;
                        i = k -1;
                    }
                    break;
                case 'y':
                    if (format[i+1] != '+' && format[i+1] != '-')
                        break;
                    if (format[i+1] && format[i+2]) {
                        for (k = i+2; k < (signed int)SDL_strlen(format) ; k++) {
                            if (SDL_isdigit(format[k]))
                                dy = 10*dy + format[k] -'0';
                            else
                                break;
                        }
                        if (format[i+1] == '-')
                            dy = -dy;
                        i = k -1;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    for (i = 0; i < n; i++) {
        result |= SDL_RenderCopy(renderer, texture, src, &dst);
        if (dest) {
            dst.w += dw;
            dst.h += dh;
            dst.x += dx;
            dst.y += dy;
        }
    }

    return result;
}

void
SDLU_RenderBegin(int mode)
{
    head = NULL;
    node = NULL;
    type = mode;
}

void
SDLU_RenderSetPoint(int x, int y)
{
    SDL_Point p;
    p.x = x;
    p.y = y;

    SDLU_RenderSetPoints(&p, 1);
}

void
SDLU_RenderSetPoints(SDL_Point* points, int num_points)
{
    int i;
    for(i = 0; i < num_points; i++) {
        node = SDLU_malloc(SDLU_PList);
        if (node == NULL)
            SDLU_ExitError("could not allocate memory", );

        node->x = points[i].x;
        node->y = points[i].y;
        DL_PREPEND(head, node);
        node = NULL;
    }
}

int
SDLU_RenderEnd(SDL_Renderer* renderer)
{
    /* only used for fill rendering */
    int i;
    int n = 0;
    SDL_Point* points = NULL;
    int result = 0;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    if (head == NULL)
        SDLU_ExitError("not enough points", -1);

    switch (type) {
        case SDLU_WIRE:

            /* for a wired polygon (outline), we just draw lines
             * the method used ensures that the last point will connect with
             * the first.
             */
            DL_FOREACH(head, node) {
                if (node->prev)
                    result |= SDL_RenderDrawLine(renderer, node->x, node->y,
                            node->prev->x, node->prev->y);
            }
            break;

        case SDLU_FILL:

            DL_FOREACH(head, node) n++;
            points = SDLU_malloc2(SDL_Point, n);

            if (!points)
                SDLU_ExitError("could not allocate memory", -1);

            /* populate the arrays */
            i = 0;
            DL_FOREACH(head, node) {
                points[i].x = node->x;
                points[i].y = node->y;
                ++i;
            }

            /* render the polygon */
            result |= SDLU_RenderFillPolygon(renderer, points, n);

            /* free temporary arrays */
            SDLU_free(points);
            break;

        default:
            SDLU_ExitError("unknown polygon mode", -1);
            break;
    }

    /* free the memory of all nodes, we don't need them anymore */
    if (head) {
        node = NULL;
        DL_FOREACH(head, node) {
            SDLU_free(node);
        }
    }

    head = NULL;
    node = NULL;

    return result;
}

int
SDLU_RenderFillPolygon(SDL_Renderer* renderer, SDL_Point* points, int n)
{
    int result = 0;
    int i;
    int y, start, end;
    int miny, maxy;
    int x1, y1;
    int x2, y2;
    int ind1, ind2;
    int num_ints;
    int *ints = NULL;

    if ( !points || n < 3 || !renderer )
        return -1;

    ints = SDLU_malloc2(int, n);
    if (ints == NULL)
        SDLU_ExitError("could not allocate memory", -1);

    miny = maxy = points[0].y;
    for (i = 1; i < n; i++) {
        if (points[i].y > maxy) maxy = points[i].y;
        if (points[i].y < miny) miny = points[i].y;
    }

    for (y = miny; y <= maxy; y++) {
        num_ints = 0;
        for (i = 0; i < n ; i++) {

            if (i == 0) { ind1 = n - 1; ind2 = 0; }
                   else { ind1 = i - 1; ind2 = i; }

            y1 = points[ind1].y;
            y2 = points[ind2].y;
            if (y1 < y2) {
                x1 = points[ind1].x;
                x2 = points[ind2].x;
            } else if (y1 > y2) {
                y2 = points[ind1].y;
                y1 = points[ind2].y;
                x2 = points[ind1].x;
                x1 = points[ind2].x;
            } else {
                continue;
            }

            if ( (y >= y1 && y < y2) || (y == maxy && y <= y2 && y > y1) ) {
                ints[num_ints++] = ((y - y1) * (x2 - x1) / (y2 -y1)) + x1;
            }
        }

        SDL_qsort(ints, num_ints, sizeof(int), SDLU_cint);

        for (i = 0; i< num_ints; i+=2) {
            start = ints[i];
            end = ints[i+1];

            result |= SDL_RenderDrawLine(renderer, start, y, end, y);
        }
    }

    return result;
}

int
SDLU_RenderDrawPolygon(SDL_Renderer* renderer, SDL_Point* points, int n)
{
    int i;
    int result = 0;

    if (renderer == NULL)
        SDLU_ExitError("invalid parameter 'renderer'", -1);

    if (n < 3 || !points)
        SDLU_ExitError("not enough points", -1);

    for (i = 0; i < n; i++) {
        if (i == 0) {
            result |= SDL_RenderDrawLine(renderer,
                    points[0].x, points[0].y, points[n-1].x, points[n-1].y);
        } else {
            result |= SDL_RenderDrawLine(renderer,
                    points[i].x, points[i].y, points[i-1].x, points[i-1].y);
        }
    }

    return result;
}
