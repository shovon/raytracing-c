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
#include "camera.h"

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
  if (world.hit(world.item, r, 0.0, MAXFLOAT, &rec))
  {
    vec3 target = vec3_add(
        rec.p, vec3_add(rec.normal, random_in_unit_sphere()));
    return vec3_scalar_mul(
        color(make_ray(rec.p, vec3_sub(target, rec.p)), world), 0.5);
  }
  vec3 unit_direction = vec3_unit_vector(r.b);
  float t = 0.5 * (unit_direction.e1 + 1.0);
  return vec3_add(
      vec3_scalar_mul(make_vec3(1.0, 1.0, 1.0), 1.0 - t),
      vec3_scalar_mul(make_vec3(0.5, 0.7, 1.0), t));
}

int main()
{
  int nx = 200;
  int ny = 100;
  int ns = 100;
  printf("P3\n%d %d\n255\n", nx, ny);

  vec3 lower_left_corner = {-2.0, -1.0, -1.0};
  vec3 horizontal = {4.0, 0.0, 0.0};
  vec3 vertical = {0.0, 2.0, 0.0};
  vec3 origin = {0.0, 0.0, 0.0};

  hitable world = make_hitable_list(2);
  hitable_list hl = *((hitable_list *)world.item);
  hl.list[0] = make_sphere(
      make_vec3(0, 0, -1), 0.5);
  hl.list[1] = make_sphere(
      make_vec3(0, -100.5, -1), 100);

  camera cam = make_camera();

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col = {0, 0, 0};
      for (int s = 0; s < ns; s++)
      {
        float u = (((float)i) + drand48()) / ((float)nx);
        float v = (((float)j) + drand48()) / ((float)ny);
        ray r = camera_get_ray(cam, u, v);
        col = vec3_add(col, color(r, world));
      }
      col = vec3_scalar_div(col, ns);
      col = make_vec3(sqrtf(col.e0), sqrtf(col.e1), sqrtf(col.e2));
      int ir = (int)(255.99 * col.e0);
      int ig = (int)(255.99 * col.e1);
      int ib = (int)(255.99 * col.e2);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }
}