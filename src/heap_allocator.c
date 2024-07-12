#include "common.h"
#include "heap.h"
#include "heap_node.h"
#include <sys/mman.h>

heap_info heap = {0};

void heap_init() {
  heap.max = HEAP_MAX_SIZE;
  heap.actual_size = 0;
  heap.addr = mmap(NULL, HEAP_MAX_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  heap.heap = NULL;
  heap.is_init = 1;
}

void *heap_alloc(size_t size) {
  if (!heap.is_init) {
    heap_init();
  }

  if (heap.contains_free_memory & (size + 1 < heap.highest_free_memory)) {
    void *addr = heap_free_alloc(size);
    return addr;
  }

  void *heap_node_addr = heap_node_alloc();
  void *addr = (void *)(heap.addr + heap.actual_size);
  heap.actual_size += size + 1;

  heap_node *new_ptr = node_init(heap_node_addr, addr, size);
  heap_add_node(new_ptr);

  return addr;
}
