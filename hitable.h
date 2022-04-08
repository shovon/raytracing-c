#ifndef HITABLE_H
#define HITABLE_H

#include <stdbool.h>

#include "ray.h"
#include "material.h"

typedef struct hit_record
{
  float t;
  vec3 p;
  vec3 normal;
  material mat;
} hit_record;

typedef struct hitable
{
  void *item;
  bool (*hit)(void *self, ray r, float t_min, float t_max, hit_record *rec);
} hitable;

#endif