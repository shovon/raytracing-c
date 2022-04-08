#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "vec3.h"
#include "material.h"

typedef struct lambertian
{
  vec3 albedo;
} lambertian;

material make_lambertian(vec3 albedo);

#endif