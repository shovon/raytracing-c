#include <stdbool.h>
#include <stdlib.h>

#include "lambertian.h"
#include "vec3.h"

bool lambertian_scatter(void *self, ray r_in, hit_record rec, vec3 *attenuation, ray *scattered)
{
  lambertian l = *((lambertian *)self);
  vec3 target = vec3_add(rec.p, vec3_add(rec.normal, random_in_unit_sphere()));
  *scattered = make_ray(rec.p, vec3_sub(target, rec.p));
  *attenuation = l.albedo;
  return true;
}

material *make_lambertian(vec3 albedo)
{
  lambertian _l = {albedo};
  lambertian *l = malloc(sizeof(lambertian));
  *l = _l;
  material _m = {l, lambertian_scatter};
  material *m = malloc(sizeof(material));
  *m = _m;
  return m;
}