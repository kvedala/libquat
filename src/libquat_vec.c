/**
 * @file libquat_vec.c
 * API Functions related to 3D vector operations.
 * @author Krishna Vedala
 */

#include <stdio.h>
#ifdef __arm__
#define LIBQUAT_ARM
#include <arm_math.h>
#else
#include <math.h>
#endif
#include <string.h>  // for memmove

#include "libquat.h"
#include "libquat_internal.h"

void vector_sub(const vec_3d *a, const vec_3d *b, vec_3d *out)
{
#ifdef LIBQUAT_ARM
    arm_sub_f32((float *)a, (float *)b, (float *)out);
#else
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
#endif
}

void vector_add(const vec_3d *a, const vec_3d *b, vec_3d *out)
{
#ifdef LIBQUAT_ARM
    arm_add_f32((float *)a, (float *)b, (float *)out);
#else
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
#endif
}

void dot_prod(const vec_3d *a, const vec_3d *b, float *dot)
{
#ifdef LIBQUAT_ARM
    arm_dot_prod_f32((float *)a, (float *)b, dot);
#else
    *dot = a->x * b->x;
    *dot += a->y * b->y;
    *dot += a->z * b->z;
#endif
}

void vector_prod(const vec_3d *a, const vec_3d *b, vec_3d *o)
{
    vec_3d out;  // better this way to avoid copying results to input vectors
                 // themselves
    out.x = a->y * b->z - a->z * b->y;
    out.y = -a->x * b->z + a->z * b->x;
    out.z = a->x * b->y - a->y * b->x;
    memmove(o, &out, sizeof(out));
}

const char *print_vector(const vec_3d *a, const char *name)
{
    static char vec_str[100];
    snprintf(vec_str, 99, "vec(%s) = (%.3g)i + (%.3g)j + (%.3g)k\n", name, a->x,
             a->y, a->z);
    return vec_str;
}

void vector_norm(const vec_3d *a, float *n)
{
    dot_prod(a, a, n);
#ifdef LIBQUAT_ARM
    arm_sqrt_f32(*n, n);
#else
    *n = sqrtf(*n);
#endif
}

libquat_err unit_vec(const vec_3d *a, vec_3d *n)
{
    float norm;
    vector_norm(a, &norm);
    if (fabsf(norm) < LIBQUAT_EPSILON)
        return LIBQUAT_DIV_BY_ZERO;

    if (norm != 1.F)  // perform division only if needed
    {
        n->x = a->x / norm;
        n->y = a->y / norm;
        n->z = a->z / norm;
    }
    return LIBQUAT_OK;
}

void get_cross_matrix(const vec_3d *a, mat_3x3 *A)
{
    float aA[] = {0., -a->z, a->y, a->z, 0., -a->x, -a->y, a->x, 0.};
    memmove(A, aA, 9 * sizeof(float));
}
