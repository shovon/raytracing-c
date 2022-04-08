#ifndef VEC3_H
#define VEC3_H

typedef struct vec3
{
  float e0;
  float e1;
  float e2;
} vec3;

vec3 vec3_add(vec3 v1, vec3 v2);

#endif