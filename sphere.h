#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hitable.h"

typedef struct sphere
{
  vec3 center;
  float radius;
  hitable_vtable vtable;
} sphere;

sphere make_sphere(vec3 center, float radius);

#endif