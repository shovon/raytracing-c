#include <stdbool.h>
#include <stdlib.h>

#include "dialectric.h"
#include "ray.h"
#include "hitable.h"
#include "vec3.h"
#include "reflect.h"
#include "refract.h"

bool dialectric_scatter(void *self, ray r_in, hit_record rec, vec3 *attenuation, ray *scattered)
{
  dialectric d = *((dialectric *)self);
  vec3 outward_normal;
  vec3 reflected = reflect(r_in.b, rec.normal);
  float ni_over_nt;
  *attenuation = make_vec3(1, 1, 1);
  vec3 refracted;
  if (vec3_dot(r_in.b, rec.normal) > 0)
  {
    outward_normal = vec3_scalar_mul(rec.normal, -1);
    ni_over_nt = d.ref_idx;
  }
  else
  {
    outward_normal = rec.normal;
    ni_over_nt = 1 / d.ref_idx;
  }
  vec3 before = refracted;
  if (refract(r_in.b, outward_normal, ni_over_nt, &refracted))
  {
    *scattered = make_ray(rec.p, refracted);
  }
  else
  {
    *scattered = make_ray(rec.p, reflected);
    return false;
  }
  return true;
}

material *make_dialectric(float ref_idx)
{
  dialectric _l = {ref_idx};
  dialectric *l = malloc(sizeof(dialectric));
  *l = _l;
  material _d = {l, dialectric_scatter};
  material *d = malloc(sizeof(material));
  *d = _d;
  return d;
}