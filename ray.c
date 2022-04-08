#include "ray.h"
#include "vec3.h"

ray make_ray(vec3 a, vec3 b)
{
  ray r = {a, b};
  return r;
}

vec3 ray_point_at_parameter(ray r, float t)
{
  return vec3_add(r.a, vec3_scalar_mul(r.b, t));
}
