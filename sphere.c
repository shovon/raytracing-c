#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "sphere.h"
#include "vec3.h"
#include "hitable.h"

bool sphere_hit(void *self, ray r, float t_min, float t_max, hit_record *rec)
{
  sphere s = *((sphere *)self);
  vec3 oc = vec3_sub(r.a, s.center);
  float a = vec3_dot(r.b, r.b);
  float b = vec3_dot(oc, r.b);
  float c = vec3_dot(oc, oc) - s.radius * s.radius;
  float discriminant = b * b - a * c;
  if (discriminant > 0)
  {
    float temp = (-b - sqrtf(b * b - a * c)) / a;
    if (temp < t_max && temp > t_min)
    {
      rec->t = temp;
      rec->p = ray_point_at_parameter(r, rec->t);
      rec->normal = vec3_scalar_div(vec3_sub(rec->p, s.center), s.radius);
      rec->mat = s.mat;
      return true;
    }
    temp = (-b + sqrtf(b * b - a * c)) / a;
    if (temp < t_max && temp > t_min)
    {
      rec->t = temp;
      rec->p = ray_point_at_parameter(r, rec->t);
      rec->normal = vec3_scalar_div(vec3_sub(rec->p, s.center), s.radius);
      rec->mat = s.mat;
      return true;
    }
  }
  return false;
}

hitable make_sphere(vec3 center, float radius, material *mat)
{
  sphere *s = malloc(sizeof(sphere));
  sphere _s = {center, radius, mat};
  *s = _s;
  hitable h = {s, sphere_hit};
  return h;
}