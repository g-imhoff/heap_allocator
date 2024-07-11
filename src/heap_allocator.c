#include "common.h"
#include "heap.h"
#include <sys/mman.h>

heap_node node_init(void *addr, size_t size) {
  heap_node init;

  init.node_size = size;
  init.addr = addr;
  init.next = NULL;

  return init;
}

void heap_add_node(heap_node new) {
  if (heap.heap == NULL) {
    heap.heap = &new;
    return;
  }

  heap_node *tmp = heap.heap;

  while (tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = &new;
}

void *heap_alloc(size_t size) {
  if (!heap.is_init) {
    heap_init();
  }

  void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  heap_node new = node_init(addr, size);
  heap_add_node(new);

  return addr;
}
