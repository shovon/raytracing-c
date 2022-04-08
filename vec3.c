#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "vec3.h"

vec3 make_vec3(float e1, float e2, float e3)
{
  vec3 v = {e1, e2, e3};
  return v;
}

float rand_min_max(float min, float max)
{
  return min + drand48() * (max - min);
}

vec3 random_vec3_min_max(float min, float max)
{
  vec3 v = {
      rand_min_max(min, max),
      rand_min_max(min, max),
      rand_min_max(min, max)};
  return v;
}

vec3 random_in_unit_sphere()
{
  vec3 p;
  while (true)
  {
    p = random_vec3_min_max(-1, 1);
    if (vec3_dot(p, p) >= 1)
    {
      continue;
    }
    break;
  }
  return p;
}

float vec3_dot(vec3 v1, vec3 v2)
{
  return v1.e0 * v2.e0 + v1.e1 * v2.e1 + v1.e2 * v2.e2;
}

vec3 vec3_cross(vec3 v1, vec3 v2)
{
  vec3 v = {
      v1.e1 * v2.e2 - v1.e2 * v2.e1,
      -(v1.e0 * v2.e2 - v1.e2 * v2.e0),
      v1.e0 * v2.e1 - v1.e1 * v2.e0};
  return v;
}

float vec3_length(vec3 v)
{
  return sqrtf(vec3_dot(v, v));
}

vec3 vec3_add(vec3 v1, vec3 v2)
{
  vec3 v = {
      v1.e0 + v2.e0,
      v1.e1 + v2.e1,
      v1.e2 + v2.e2};
  return v;
}

vec3 vec3_sub(vec3 v1, vec3 v2)
{
  vec3 mul = vec3_scalar_mul(v1, -1);
  vec3 v = vec3_add(v1, vec3_scalar_mul(v2, -1));
  return v;
}

vec3 vec3_mul(vec3 v1, vec3 v2)
{
  vec3 v = {v1.e0 * v2.e0,
            v1.e1 * v2.e1,
            v1.e2 * v2.e2};
  return v;
}

vec3 vec3_div(vec3 v1, vec3 v2)
{
  vec3 v = {v1.e0 / v2.e0,
            v1.e1 / v2.e1,
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

vec3 vec3_unit_vector(vec3 v)
{
  return vec3_scalar_div(v, vec3_length(v));
}
