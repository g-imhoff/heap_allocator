#pragma once

#include "common.h"

#define HEAP_MAX_SIZE 64000000

typedef struct h_node {
  size_t node_size;
  void *addr;
  struct h_node *next;
} heap_node;

typedef struct {
  int is_init;
  size_t max;
  size_t actual_size;
  void *addr;
  struct h_node *heap;
} heap_info;

extern heap_info heap;

void *heap_alloc(size_t size);
void heap_free(void *addr);
