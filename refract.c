#include <math.h>
#include <stdbool.h>

#include "refract.h"
#include "vec3.h"

bool refract(vec3 v, vec3 n, float ni_over_nt, vec3 *refracted)
{
  vec3 uv = vec3_unit_vector(v);
  float dt = vec3_dot(uv, n);
  float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0)
  {
    *refracted = vec3_sub(
        vec3_scalar_mul(vec3_sub(uv, vec3_scalar_mul(n, dt)), ni_over_nt),
        vec3_scalar_mul(n, sqrtf(discriminant)));
    return true;
  }

  return false;
}