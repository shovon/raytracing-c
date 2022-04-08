#ifndef DIALECTRIC_H
#define DIALECTRIC_H

#include "material.h"

typedef struct dialectric
{
  float ref_idx;
} dialectric;

material *make_dialectric(float ref_idx);

#endif