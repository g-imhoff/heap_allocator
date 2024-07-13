#pragma once

#include "common.h"
#include "heap_node.h"

// This is the maximum heap size (64mb)
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

// allows the heap to be used in the rest of the program
extern heap_info heap;

void heap_init();
void add_actual_size(size_t size);
void print_heap_node();
size_t heap_sizeof(void *addr);
void *heap_find_smallest(size_t size);
void heap_frag(void *addr, size_t size_needed);
