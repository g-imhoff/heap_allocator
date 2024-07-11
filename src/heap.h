#pragma once

#include "heap.h"

typedef struct h_node {
  size_t node_size;
  struct h_node *next;
} heap_node;

typedef struct {
  size_t max;
  size_t actual_size;
  heap_node heap;
} heap_info;
