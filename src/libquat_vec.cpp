/**
 * @file
 * @brief API Functions related to 3D vector operations.
 * @author Krishna Vedala
 */

#ifdef __arm__
#define LIBQUAT_ARM
#include <arm_math.h>
#else
#include <cmath>
#endif
#include <iostream>

#include "libquat.h"
#include "libquat_internal.h"

vec_3d operator-(const vec_3d &a, const vec_3d &b)
{
    vec_3d result = {0.f};
#ifdef LIBQUAT_ARM
    arm_sub_f32((float *)&a, (float *)&b, (float *)&result);
#else
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
#endif

    return result;
}

vec_3d vector_sub(const vec_3d *a, const vec_3d *b, vec_3d *out)
{
    auto result = *a - *b;
    if (out)
        *out = result;

    return result;
}

vec_3d operator+(const vec_3d &a, const vec_3d &b)
{
    vec_3d result = {0.f};
#ifdef LIBQUAT_ARM
    arm_sub_f32((float *)&a, (float *)&b, (float *)&result);
#else
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
#endif

    return result;
}

vec_3d vector_add(const vec_3d *a, const vec_3d *b, vec_3d *out)
{
    auto result = *a + *b;
    if (out)
        *out = result;

    return result;
}

float operator*(const vec_3d &a, const vec_3d &b)
{
    float result = 0.f;
#ifdef LIBQUAT_ARM
    arm_dot_prod_f32((float *)a, (float *)b, result);
#else
    result = a.x * b.x;
    result += a.y * b.y;
    result += a.z * b.z;
#endif

    return result;
}

float dot_prod(const vec_3d *a, const vec_3d *b, float *dot)
{
    float result = *a * *b;

    if (dot)  // if not null
        *dot = result;

    return result;
}

vec_3d operator^(const vec_3d &a, const vec_3d &b)
{
    vec_3d out;  // better this way to avoid copying results to input vectors
                 // themselves
    out.x = a.y * b.z - a.z * b.y;
    out.y = -a.x * b.z + a.z * b.x;
    out.z = a.x * b.y - a.y * b.x;

    return out;
}

vec_3d vector_prod(const vec_3d *a, const vec_3d *b, vec_3d *o)
{
    auto result = *a ^ *b;

    if (o)  // if not null
        *o = result;

    return result;
}

const char *print_vector(const vec_3d *a, const char *name)
{
    static char vec_str[100];
    snprintf(vec_str, 99, "vec(%s) = (%.3g)i + (%.3g)j + (%.3g)k\n", name, a->x,
             a->y, a->z);
    return vec_str;
}

float operator~(const vec_3d &a)
{
    float result = a * a;
#ifdef LIBQUAT_ARM
    arm_sqrt_f32(&result, result);
#else
    result = sqrtf(result);
#endif

    return result;
}

float vector_norm(const vec_3d *a, float *n)
{
    auto result = ~(*a);

    if (n)  // if not null
        *n = result;

    return result;
}

vec_3d unit_vec(const vec_3d *a, vec_3d *n)
{
    float norm = ~(*a);
    vec_3d result = {0.f};

    if (fabsf(norm) < LIBQUAT_EPSILON)
    {
        std::cerr << __func__ << ": Division by zero.";
        return result;
    }

    if (norm != 1.F)  // perform division only if needed
    {
        result.x = a->x / norm;
        result.y = a->y / norm;
        result.z = a->z / norm;
    }
    if (n)
        *n = result;

    return result;
}

void get_cross_matrix(const vec_3d *a, mat_3x3 *A)
{
    float aA[] = {0., -a->z, a->y, a->z, 0., -a->x, -a->y, a->x, 0.};
    memmove(A, aA, 9 * sizeof(float));
}
