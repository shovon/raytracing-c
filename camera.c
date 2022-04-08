#include <stdio.h>
#include <math.h>

#include "camera.h"
#include "vec3.h"

camera make_camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect)
{
  camera c;
  vec3 u, v, w;
  float theta = vfov * M_PI / 180;
  float half_height = tan(theta / 2);
  float half_width = aspect * half_height;
  c.origin = lookfrom;
  w = vec3_unit_vector(vec3_sub(lookfrom, lookat));
  u = vec3_unit_vector(vec3_cross(vup, w));
  v = vec3_cross(w, u);
  c.lower_left_corner = make_vec3(-half_width, -half_height, -1);
  c.lower_left_corner = vec3_sub(
      c.origin,
      vec3_add(
          vec3_scalar_mul(u, half_width),
          vec3_add(vec3_scalar_mul(v, half_height), w)));
  c.horizontal = vec3_scalar_mul(u, 2 * half_width);
  c.vertical = vec3_scalar_mul(v, 2 * half_height);
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