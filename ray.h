#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
  vec3 a;
  vec3 b;
} ray;

ray make_ray(vec3, vec3);

vec3 ray_point_at_parameter(ray, float);

#endif