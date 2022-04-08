#ifndef VEC3_H
#define VEC3_H

typedef struct vec3
{
  float e0;
  float e1;
  float e2;
} vec3;

float vec3_dot(vec3, vec3);
float vec3_length(vec3);
vec3 vec3_add(vec3, vec3);
vec3 vec3_sub(vec3, vec3);
vec3 vec3_mul(vec3, vec3);
vec3 vec3_div(vec3, vec3);
vec3 vec3_scalar_mul(vec3, float);
vec3 vec3_scalar_div(vec3, float);

#endif