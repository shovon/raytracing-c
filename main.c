#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"

vec3 color(ray r, hitable world, int depth)
{
  hit_record rec;
  if (world.hit(world.item, r, 0.001, MAXFLOAT, &rec))
  {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat->scatter(rec.mat->item, r, rec, &attenuation, &scattered))
    {
      return vec3_mul(attenuation, color(scattered, world, depth + 1));
    }
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

  hitable world = make_hitable_list(4);
  hitable_list hl = *((hitable_list *)world.item);
  hl.list[0] = make_sphere(
      make_vec3(0, 0, -1), 0.5, make_lambertian(make_vec3(0.8, 0.3, 0.3)));
  hl.list[1] = make_sphere(
      make_vec3(0, -100.5, -1), 100, make_lambertian(make_vec3(0.8, 0.8, 0.0)));
  hl.list[2] = make_sphere(
      make_vec3(1, 0, -1), 0.5, make_metal(make_vec3(0.8, 0.6, 0.2), 0.3));
  hl.list[3] = make_sphere(
      make_vec3(-1, 0, -1), 0.5, make_metal(make_vec3(0.8, 0.8, 0.8), 1));

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
        col = vec3_add(col, color(r, world, 0));
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