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

#ifndef SDLU_MATH_H
#define SDLU_MATH_H

#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief A 4x4 matrix
 */
typedef struct {
    double m[4][4]; /** matrix contents **/
} SDLU_Matrix;

/**
 *  \brief A vertex in 4D space
 */
typedef struct {
    double x, y, z, w;
} SDLU_Vector;

/**
 *  \brief Returns a new vector v = (x, y, z, w)
 *
 *  \param x, y, z, w Coordinates of the new vector
 */
extern DECLSPEC SDLU_Vector SDLCALL SDLU_NewVector(
        double x, double y, double z, double w
);

/**
 *  \brief Returns the vector v = a + b
 *
 *  \param a, b Vectors to add
 *  \param v Will be filled with the vector 'a + b'
 */
extern DECLSPEC void SDLCALL SDLU_AddVectors(
        SDLU_Vector a, SDLU_Vector b,
        SDLU_Vector *v
);

/**
 *  \brief Returns the vector v = a - b
 *
 *  \param a, b Vectors to substract
 *  \param v Will be filled with the vector 'a - b'
 */
extern DECLSPEC void SDLCALL SDLU_SubVectors(
        SDLU_Vector a, SDLU_Vector b,
        SDLU_Vector *v
);

/**
 *  \brief Calculates the vector v = k*a, k E R and u vector
 *
 *  \param a Vector to multiply
 *  \param k Real number to multiply the vector with
 *  \param v Will be filled with the result of k*a
 */
extern DECLSPEC void SDLCALL SDLU_ScaleVector(
        SDLU_Vector a, double k,
        SDLU_Vector *v
);

/**
 *  \brief Returns the dot (scalar) product of vectors a and b
 *
 *  \param a, b Vectors for which to calculate the dot product
 *  \param result Will be filled with the dot product 'a (dot) b'
 */
extern DECLSPEC void SDLCALL SDLU_DotProduct(
        SDLU_Vector a, SDLU_Vector b,
        double *result
);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_MATH_H */


