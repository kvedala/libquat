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
#include "libquat.h"

void dot_prod(vec_3d *a, vec_3d *b, float *dot)
{
#ifdef LIBQUAT_ARM
  arm_dot_prod_f32((float*) a, (float*) b, dot);
#else
  *dot = a->x * b->x;
  *dot += a->y * b->y;
  *dot += a->z * b->z;
#endif
}


void vector_prod (vec_3d *a, vec_3d *b, vec_3d *o)
{
  o->x =  a->y * b->z - a->z * b->y;
  o->y = -a->x * b->z + a->z * b->x;
  o->z =  a->x * b->y - a->y * b->x;
}


void print_vector(vec_3d *a, const char *name)
{
  printf("vec(%s) = (%.3g)i + (%.3g)j + (%.3g)k\n", 
      name, a->x, a->y, a->z);
}


void vector_norm(vec_3d *a, float *n)
{
  dot_prod(a, a, n);
#ifdef LIBQUAT_ARM
  arm_sqrt_f32(*n, n);
#else
  *n = sqrtf(*n);
#endif
}

void unit_vec(vec_3d *a, vec_3d *n)
{
  float norm;
  vector_norm(a, &norm);
  n->x = a->x / norm;
  n->y = a->y / norm;
  n->z = a->z / norm;
}
