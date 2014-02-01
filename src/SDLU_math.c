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
