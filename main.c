#include <stdio.h>

#include "vec3.h"

int main()
{
  int nx = 200;
  int ny = 100;
  printf("P3\n%d %d\n255\n", nx, ny);

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col = {
          ((float)i) / ((float)nx), ((float)j) / ((float)ny), 0.2};
      int ir = (int)(255.99 * col.e0);
      int ig = (int)(255.99 * col.e1);
      int ib = (int)(255.99 * col.e2);
      printf("%d %d %d\n", ir, ig, ib);
    }
  }
}