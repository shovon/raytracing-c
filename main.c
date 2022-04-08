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
#include "dialectric.h"

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

hitable random_scene()
{
  int n = 500;
  hitable world = make_hitable_list(n + 1);
  hitable_list *hl = ((hitable_list *)world.item);
  hl->list[0] = make_sphere(make_vec3(0, -1000, 0), 1000, make_lambertian(make_vec3(0.5, 0.5, 0.5)));
  int i = 1;
  for (int a = -11; a < 11; a++)
  {
    for (int b = -11; b < 11; b++)
    {
      float choose_mat = drand48();
      vec3 center = {a + 0.9 * drand48(), 0.2, b + 0.9 * drand48()};
      if (vec3_length(vec3_sub(center, make_vec3(4, 0.2, 0))) > 0.9)
      {
        if (choose_mat < 0.8)
        {
          hl->list[i++] = make_sphere(
              center,
              0.2,
              make_lambertian(
                  make_vec3(
                      drand48() * drand48(),
                      drand48() * drand48(),
                      drand48() * drand48())));
        }
        else if (choose_mat < 0.95)
        {
          hl->list[i++] = make_sphere(
              center,
              0.2,
              make_metal(
                  make_vec3(
                      0.5 * (1 + drand48()),
                      0.5 * (1 + drand48()),
                      0.5 * (1 + drand48())),
                  drand48() * 0.5));
        }
        else
        {
          hl->list[i++] = make_sphere(center, 0.2, make_dialectric(1.5));
        }
      }
    }
  }

  hl->list[i++] = make_sphere(make_vec3(0, 1, 0), 1, make_dialectric(1.5));
  hl->list[i++] = make_sphere(make_vec3(-4, 1, 0), 1, make_lambertian(make_vec3(0.4, 0.2, 0.1)));
  hl->list[i++] = make_sphere(make_vec3(4, 1, 0), 1, make_metal(make_vec3(0.7, 0.6, 0.5), 0));

  hl->list_size = i;
  world.item = (void *)hl;
  return world;
}

int main()
{
  int nx = 1024;
  int ny = 576;
  int ns = 100;
  printf("P3\n%d %d\n255\n", nx, ny);

  // hitable world = make_hitable_list(5);
  // hitable_list hl = *((hitable_list *)world.item);
  // hl.list[0] = make_sphere(
  //     make_vec3(0, 0, -1), 0.5, make_lambertian(make_vec3(0.1, 0.2, 0.5)));
  // hl.list[1] = make_sphere(
  //     make_vec3(0, -100.5, -1), 100, make_lambertian(make_vec3(0.8, 0.8, 0.0)));
  // hl.list[2] = make_sphere(
  //     make_vec3(1, 0, -1), 0.5, make_metal(make_vec3(0.8, 0.6, 0.2), 1));
  // hl.list[3] = make_sphere(
  //     make_vec3(-1, 0, -1), 0.5, make_dialectric(1.5));
  // hl.list[4] = make_sphere(
  //     make_vec3(-1, 0, -1), -0.45, make_dialectric(1.5));

  // hitable world = make_hitable_list(2);
  // hitable_list hl = *((hitable_list *)world.item);
  // float R = cos(M_PI / 4);
  // hl.list[0] = make_sphere(
  //     make_vec3(-R, 0, -1), R, make_lambertian(make_vec3(0, 0, 1)));
  // hl.list[1] = make_sphere(
  //     make_vec3(R, 0, -1), R, make_lambertian(make_vec3(1, 0, 0)));

  hitable world = random_scene();

  vec3 lookfrom = {12, 2, 4};
  vec3 lookat = {0, 1, 0};
  float dist_to_focus = vec3_length(vec3_sub(lookfrom, lookat));
  float aperture = 0.2;

  camera cam = make_camera(
      lookfrom,
      lookat,
      make_vec3(0, 1, 0),
      20,
      ((float)nx) / ((float)ny), aperture, dist_to_focus);

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