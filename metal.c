#include <stdbool.h>
#include <stdlib.h>

#include "metal.h"
#include "reflect.h"
#include "ray.h"
#include "material.h"

bool metal_scatter(void *self, ray r_in, hit_record rec, vec3 *attenuation, ray *scattered)
{
  metal m = *((metal *)self);
  vec3 reflected = reflect(vec3_unit_vector(r_in.b), rec.normal);
  *scattered = make_ray(
      rec.p,
      vec3_add(reflected, vec3_scalar_mul(random_in_unit_sphere(), m.fuzz)));
  *attenuation = m.albedo;
  return (vec3_dot(scattered->b, rec.normal) > 0);
}

material *make_metal(vec3 albedo, float fuzz)
{
  metal _l = {albedo, fuzz};
  metal *l = malloc(sizeof(metal));
  *l = _l;
  material _m = {l, metal_scatter};
  material *m = malloc(sizeof(material));
  *m = _m;
  return m;
}