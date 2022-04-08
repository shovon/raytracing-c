#include "vec3.h"

vec3 vec3_add(vec3 v1, vec3 v2)
{
  vec3 v = {v1.e0 + v2.e0, v1.e1 + v2.e2, v1.e2 + v2.e2};
  return v;
}