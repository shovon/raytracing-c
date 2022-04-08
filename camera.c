#include <stdio.h>
#include "camera.h"

camera make_camera()
{
  camera c = {
      make_vec3(0, 0, 0),
      make_vec3(-2.0, -1.0, -1.0),
      make_vec3(4.0, 0.0, 0.0),
      make_vec3(0, 2, 0)};
  return c;
}

ray camera_get_ray(camera c, float u, float v)
{
  vec3 b = vec3_add(
      c.lower_left_corner,
      vec3_sub(
          vec3_add(
              vec3_scalar_mul(c.horizontal, u),
              vec3_scalar_mul(c.vertical, v)),
          c.origin));

  ray r = {
      c.origin,
      b};
  return r;
}