#pragma once

#include "common.h"

typedef struct h_node {
  size_t node_size;
  void *addr;
  struct h_node *next;
} heap_node;

heap_node *node_init(void *heap_node_addr, void *addr, size_t size);
void heap_add_node(heap_node *node_ptr);
void print_heap_node();
