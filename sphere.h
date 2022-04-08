#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "vec3.h"

typedef struct sphere
{
  vec3 center;
  float radius;
} sphere;

hitable make_sphere(vec3 center, float radius);

#endif