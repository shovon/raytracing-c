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
} camera;

camera make_camera();

ray camera_get_ray(camera, float, float);

#endif