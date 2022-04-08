#include "vec3.h"
#include <math.h>

float vec3_dot(vec3 v1, vec3 v2)
{
  return v1.e0 * v2.e0 + v1.e1 * v2.e1 + v1.e2 * v2.e2;
}

float vec3_length(vec3 v)
{
  return sqrtf(vec3_dot(v, v));
}

vec3 vec3_add(vec3 v1, vec3 v2)
{
  vec3 v = {
      v1.e0 + v2.e0,
      v1.e1 + v2.e2,
      v1.e2 + v2.e2};
  return v;
}

vec3 vec3_sub(vec3 v1, vec3 v2)
{
  vec3 v = vec3_add(v1, vec3_scalar_mul(v1, -1));
  return v;
}

vec3 vec3_mul(vec3 v1, vec3 v2)
{
  vec3 v = {v1.e0 * v2.e0,
            v1.e1 * v2.e2,
            v1.e2 * v2.e2};
  return v;
}

vec3 vec3_div(vec3 v1, vec3 v2)
{
  vec3 v = {v1.e0 / v2.e0,
            v1.e1 / v2.e2,
            v1.e2 / v2.e2};
  return v;
}

vec3 vec3_scalar_mul(vec3 v, float c)
{
  vec3 o = {v.e0 * c, v.e1 * c, v.e2 * c};
  return o;
}

vec3 vec3_scalar_div(vec3 v, float c)
{
  return vec3_scalar_mul(v, 1 / c);
}
