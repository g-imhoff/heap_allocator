#include "common.h"
#include "heap.h"
#include "heap_node.h"

void heap_free(void *addr) {
  heap_node *tmp = heap.heap;
  size_t size = heap_sizeof(addr);

  if (heap.contains_free_memory) {

    heap.highest_free_memory =
        size > heap.highest_free_memory ? size : heap.highest_free_memory;
  } else {
    heap.contains_free_memory = true;
    heap.highest_free_memory = size;
  }

  while (tmp) {
    if (tmp->addr == addr) {
      tmp->free = true;

      return;
    }

    tmp = tmp->next;
  }

  heap.actual_size -= size;
}
