#ifndef REFRACT_H
#define REFRACT_H

#include <stdbool.h>

#include "vec3.h"

bool refract(vec3 v, vec3 n, float ni_over_nt, vec3 *refracted);

#endif