#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

typedef struct hitable_list
{
  hitable *list;
  int list_size;
} hitable_list;

hitable make_hitable_list(int list_size);

#endif