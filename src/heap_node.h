#pragma once

#include "common.h"

typedef struct h_node {
  size_t node_size;
  void *addr;
  bool free;
  struct h_node *next;
  struct h_node *previous;
} heap_node;

heap_node *node_init(void *heap_node_addr, void *addr, size_t size);
void heap_add_node(heap_node *node_ptr);
void print_heap_node();
size_t heap_sizeof(void *addr);
void *heap_node_alloc();
void *heap_free_alloc(size_t size);
void heap_add_node_pos(heap_node *node_ptr, int pos);
