#pragma once

#include "common.h"
#include "heap.h"

typedef struct h_node {
  size_t node_size;
  void *addr;
  bool free;
  struct h_node *next;
  struct h_node *previous;
} heap_node;

void *heap_node_alloc();
heap_node *node_init(void *heap_node_addr, void *addr, size_t size);
void heap_add_node(heap_node *node_ptr);
void heap_add_node_pos(heap_node *node_ptr, int pos);
