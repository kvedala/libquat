#include <math.h>
#include "libquat.h"

float dot_prod(3d_vec *a, 3d_vec *b)
{
  float result = a->x * b->x;
  result += a->y * b->y;
  result += a->z * b->z;
  return result;
}
