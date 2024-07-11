#include "common.h"
#include "heap.h"
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
