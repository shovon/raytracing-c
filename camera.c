#include <math.h>
#include <stdlib.h>

#include "camera.h"
#include "vec3.h"

camera make_camera(
    vec3 lookfrom,
    vec3 lookat,
    vec3 vup,
    float vfov,
    float aspect,
    float aperture,
    float focus_dist)
{
  camera c;
  c.lens_radius = aperture / 2;
  float theta = vfov * M_PI / 180;
  float half_height = tan(theta / 2);
  float half_width = aspect * half_height;
  c.origin = lookfrom;
  c.w = vec3_unit_vector(vec3_sub(lookfrom, lookat));
  c.u = vec3_unit_vector(vec3_cross(vup, c.w));
  c.v = vec3_cross(c.w, c.u);
  c.lower_left_corner = vec3_sub(
      c.origin,
      vec3_add(
          vec3_scalar_mul(c.u, half_width * focus_dist),
          vec3_add(
              vec3_scalar_mul(c.v, half_height * focus_dist),
              vec3_scalar_mul(c.w, focus_dist))));
  c.horizontal = vec3_scalar_mul(c.u, 2 * half_width * focus_dist);
  c.vertical = vec3_scalar_mul(c.v, 2 * half_height * focus_dist);
  return c;
}

ray camera_get_ray(camera c, float s, float t)
{
  vec3 rd = vec3_scalar_mul(random_in_unit_sphere(), c.lens_radius);
  vec3 offset = vec3_add(
      vec3_scalar_mul(c.u, rd.e0),
      vec3_scalar_mul(c.v, rd.e1));

  vec3 b = vec3_add(
      c.lower_left_corner,
      vec3_sub(
          vec3_add(
              vec3_scalar_mul(c.horizontal, s),
              vec3_scalar_mul(c.vertical, t)),
          vec3_add(c.origin, offset)));

  ray r = {
      vec3_add(c.origin, offset),
      b};
  return r;
}