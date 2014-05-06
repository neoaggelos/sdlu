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

SDLU_Vector
SDLU_NewVector(double x, double y, double z, double w)
{
    SDLU_Vector v;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;

    return v;
}

void
SDLU_AddVectors(SDLU_Vector a, SDLU_Vector b, SDLU_Vector *v)
{
    if (v) {
        v->x = a.x + b.x;
        v->y = a.y + b.y;
        v->z = a.z + b.z;
        v->w = a.w + b.w;
    }
}

void
SDLU_SubVectors(SDLU_Vector a, SDLU_Vector b, SDLU_Vector *v)
{
    if (v) {
        v->x = a.x - b.x;
        v->y = a.y - b.y;
        v->z = a.z - b.z;
        v->w = a.w - b.w;
    }
}

void
SDLU_DotProduct(SDLU_Vector a, SDLU_Vector b, double *result)
{
    if (result) {
        *result = (a.x*b.x) + (a.y*b.y) + (a.z*b.z) + (a.w*b.w);
    }
}

void
SDLU_ScaleVector(SDLU_Vector a, double k, SDLU_Vector *v)
{
    if (v) {
        v->x = a.x * k;
        v->y = a.y * k;
        v->z = a.z * k;
        v->w = a.w * k;
    }
}
