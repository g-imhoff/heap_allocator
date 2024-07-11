#include "common.h"
#include "heap.h"

void heap_free(void *addr) {
  heap_node *tmp = heap.heap;
  while (tmp) {
    if (tmp->addr == addr) {
      tmp->free = true;

      return;
    }

    tmp = tmp->next;
  }
}
