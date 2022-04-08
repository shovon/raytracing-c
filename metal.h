#ifndef METAL_H
#define METAL_H

#include "vec3.h"
#include "material.h"

typedef struct metal
{
  vec3 albedo;
  float fuzz;
} metal;

material *make_metal(vec3 albedo, float fuzz);

#endif