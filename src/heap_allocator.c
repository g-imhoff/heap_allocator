#include "common.h"
#include "heap.h"
#include <sys/mman.h>

heap_info heap = {0};

/**
 *
 * This just init the node lonely
 *
 */

heap_node *node_init(void *addr, size_t size) {
  heap_node *new_ptr = addr - 1;

  new_ptr->addr = addr;
  new_ptr->node_size = size;
  new_ptr->next = NULL;

  return new_ptr;
}

void heap_add_node(heap_node *node_ptr) {
  if (heap.heap == NULL) {
    heap.heap = node_ptr;
  }

  heap_node *tmp = heap.heap;
  while (tmp) {
    tmp = tmp->next;
  }

  tmp->next = node_ptr;
}

void *heap_alloc(size_t size) {
  if (!heap.is_init) {
    heap_init();
  }

  void *addr = (void *)(heap.addr + heap.actual_size);

  // heap_node *new_ptr = node_init(addr, size);
  // heap_add_node(new_ptr);

  heap.actual_size += size;

  return addr;
}
