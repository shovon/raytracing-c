#ifndef HITABLE_H
#define HITABLE_H

#include <stdbool.h>

#include "ray.h"

typedef struct hit_record
{
  float t;
  vec3 p;
  vec3 normal;
} hit_record;

typedef struct hitable_vtable
{
  bool (*hit)(void *self, ray r, float t_min, float t_max, hit_record *rec);
} hitable_vtable;

#endif