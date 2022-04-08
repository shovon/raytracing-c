#include "ray.h"
#include "vec3.h"

vec3 ray_point_at_parameter(ray r, float t)
{
  return vec3_add(r.a, vec3_scalar_mul(r.b, t));
}
