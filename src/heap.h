#pragma once

#include "common.h"
#include "heap_node.h"

#define HEAP_MAX_SIZE 64000000

typedef struct {
  // Check if the heap as been initialized
  int is_init;

  // Information on the size of the heap
  size_t max;
  size_t actual_size;

  // The starting address of the heap
  void *addr;

  // Information on free memory
  bool contains_free_memory;
  size_t highest_free_memory;

  // The head of the linked list given information on memory allocated
  struct h_node *heap;
} heap_info;

extern heap_info heap;

extern void *heap_alloc(size_t size);
extern void heap_free(void *addr);
