#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct camera
{
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u;
  vec3 v;
  vec3 w;
  float lens_radius;
} camera;

camera make_camera(vec3, vec3, vec3, float, float, float, float);

ray camera_get_ray(camera, float, float);

#endif