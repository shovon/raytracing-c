#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"

float hit_sphere(vec3 center, float radius, ray r)
{
  vec3 oc = vec3_sub(r.a, center);
  float a = vec3_dot(r.b, r.b);
  float b = 2.0 * vec3_dot(oc, r.b);
  float c = vec3_dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  if (discriminant < -1.0)
  {
    return -1.0;
  }
  return (-b - sqrtf(discriminant)) / (2.0 * a);
}

vec3 color(ray r, hitable world)
{
  hit_record rec;
  float t = hit_sphere(make_vec3(0, 0, -1), 0.5, r);
  if (world.hit(world.item, r, 0.0, MAXFLOAT, &rec))
  {
    return vec3_scalar_mul(
        make_vec3(rec.normal.e0 + 1, rec.normal.e1 + 1, rec.normal.e2 + 1), 0.5);
  }
  vec3 unit_direction = vec3_unit_vector(r.b);
  t = 0.5 * (unit_direction.e1 + 1.0);
  return vec3_add(
      vec3_scalar_mul(make_vec3(1.0, 1.0, 1.0), 1.0 - t),
      vec3_scalar_mul(make_vec3(0.5, 0.7, 1.0), t));
}

int main()
{
  int nx = 200;
  int ny = 100;
  printf("P3\n%d %d\n255\n", nx, ny);

  vec3 lower_left_corner = {-2.0, -1.0, -1.0};
  vec3 horizontal = {4.0, 0.0, 0.0};
  vec3 vertical = {0.0, 2.0, 0.0};
  vec3 origin = {0.0, 0.0, 0.0};

  hitable list = make_hitable_list(2);
  hitable_list hl = *((hitable_list *)list.item);
  hl.list[0] = make_sphere(
      make_vec3(0, 0, -1), 0.5);
  hl.list[1] = make_sphere(
      make_vec3(0, -100.5, -1), 100);

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      float u = ((float)i) / ((float)nx);
      float v = ((float)j) / ((float)ny);
      ray r = {
          origin,
          vec3_add(
              lower_left_corner,
              vec3_add(
                  vec3_scalar_mul(horizontal, u),
                  vec3_scalar_mul(vertical, v)))};
      vec3 col = color(r, list);
      int ir = (int)(255.99 * col.e0);
      int ig = (int)(255.99 * col.e1);
      int ib = (int)(255.99 * col.e2);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }
}