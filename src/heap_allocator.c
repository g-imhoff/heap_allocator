#include "common.h"
#include "heap.h"
#include <sys/mman.h>

heap_info heap = {0};

/**
 *
 * This just init the node lonely
 *
 */

heap_node *node_init(void *heap_node_addr, void *addr, size_t size) {
  heap_node *new_ptr = heap_node_addr;

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
  while (tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = node_ptr;
}

void *heap_alloc(size_t size) {
  if (!heap.is_init) {
    heap_init();
  }

  void *heap_node_addr = (void *)(heap.addr + heap.actual_size);
  heap.actual_size += sizeof(heap_node) + 1;
  void *addr = (void *)(heap.addr + heap.actual_size);
  heap.actual_size += size + 1;

  printf("c calculated address : %p, heap_node calculated address : %p\n",
         (void *)addr, (void *)heap_node_addr);

  heap_node *new_ptr = node_init(heap_node_addr, addr, size);
  heap_add_node(new_ptr);

  return addr;
}
