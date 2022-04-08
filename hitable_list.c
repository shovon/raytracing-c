#include <stdbool.h>
#include <stdlib.h>

#include "hitable.h"
#include "hitable_list.h"

bool hitable_list_hit(void *self, ray r, float t_min, float t_max, hit_record *rec)
{
  hitable_list h = *((hitable_list *)self);
  hit_record temp_rec;
  bool hit_anything = false;
  float closest_so_far = t_max;

  for (int i = 0; i < h.list_size; i++)
  {
    if (h.list[i].hit(h.list[i].item, r, t_min, closest_so_far, &temp_rec))
    {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      *rec = temp_rec;
    }
  }
  return hit_anything;
}

hitable make_hitable_list(int list_size)
{
  hitable_list *hl = malloc(sizeof(hitable_list));
  hitable_list _hl = {
      malloc((sizeof(hitable_list)) * list_size),
      list_size};
  *hl = _hl;
  hitable h = {hl, hitable_list_hit};
  return h;
}