#include "common.h"
#include "heap.h"
#include <sys/mman.h>

/**
 *
 * This just init the node lonely
 *
 */
heap_node node_init(void *addr, size_t size) {
  heap_node init;

  init.node_size = size;
  init.addr = addr;
  init.next = NULL;

  return init;
}

void heap_add_node(void *addr, size_t size) {}

void *heap_alloc(size_t size) {
  if (!heap.is_init) {
    heap_init();
  } else if (heap.actual_size + size >= heap.max) {
    perror("Heap no more size");
  }

  void *addr = heap.addr + heap.actual_size;

  heap_node new = node_init(addr, size);
  heap_add_node(addr, size);

  heap.actual_size += size;

  return addr;
}
