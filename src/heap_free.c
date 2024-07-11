#include "common.h"
#include "heap.h"
#include "heap_node.h"

void heap_free(void *addr) {
  heap_node *tmp = heap.heap;

  if (heap.contains_free_memory) {
    size_t size = heap_sizeof(addr);

    heap.highest_free_memory =
        size > heap.highest_free_memory ? size : heap.highest_free_memory;
  } else {
    heap.contains_free_memory = true;
    heap.highest_free_memory = heap_sizeof(addr);
  }

  while (tmp) {
    if (tmp->addr == addr) {
      tmp->free = true;

      addr = NULL;
      return;
    }

    tmp = tmp->next;
  }

  addr = NULL;
}
