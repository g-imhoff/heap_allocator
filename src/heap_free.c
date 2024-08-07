#include "heap_free.h"

void heap_free(void *addr) {
  heap_node *tmp = heap.heap;

  // we search the size of the memory that we have free
  size_t size = heap_sizeof(addr);
  // change the heap information in function
  if (heap.contains_free_memory) {
    heap.highest_free_memory =
        size > heap.highest_free_memory ? size : heap.highest_free_memory;
  } else {
    heap.contains_free_memory = true;
    heap.highest_free_memory = size;
  }

  // change the status of the heap node
  while (tmp) {
    if (tmp->addr == addr) {
      tmp->free = true;

      return;
    }

    tmp = tmp->next;
  }
}

void heap_unfree(void *addr) {
  // set the heap_node corresponding to addr that is not free anymore
  heap_node *tmp = heap.heap;

  while (tmp) {
    if (tmp->addr == addr) {
      tmp->free = false;
    }

    tmp = tmp->next;
  }
}

void *heap_free_alloc(size_t size) {
  void *addr = heap_find_smallest(size);
  heap_frag(addr, size);
  heap_unfree(addr);

  return addr;
}
