#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "hitable.h"

typedef struct material
{
  bool (*scatter)(ray r_in, hit_record rec, vec3 *attenuation, ray *scattered);
} material;

#endif