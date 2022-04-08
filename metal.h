#ifndef METAL_H
#define METAL_H

#include "vec3.h"

typedef struct metal
{
  vec3 albedo;
} metal;

material make_metal(vec3 albedo);

#endif