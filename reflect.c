#include "reflect.h"
#include "vec3.h"

vec3 reflect(vec3 v, vec3 n)
{
  return vec3_sub(
      v,
      vec3_scalar_mul(n, vec3_dot(v, n) * 2));
}