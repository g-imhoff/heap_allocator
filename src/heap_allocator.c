#include "common.h"
#include "heap.h"
#include "heap_node.h"
#include <sys/mman.h>

// init the heap at 0 everywhere
heap_info heap = {0};

void heap_init() {
  // init the heap and is memory needed
  heap.max = HEAP_MAX_SIZE;
  heap.actual_size = 0;
  // call mmap and ask him to give him 64mb of data
  heap.addr = mmap(NULL, HEAP_MAX_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  heap.heap = NULL;
  heap.is_init = 1;
}

void *heap_alloc(size_t size) {
  // init the heap in case it's not already made
  if (!heap.is_init) {
    heap_init();
  }

  // in case it contains free memory in the heap, and there is enough memory
  // free for our allocation, the alloc in the free memory
  if (heap.contains_free_memory & (size + 1 < heap.highest_free_memory)) {
    void *addr = heap_free_alloc(size);
    return addr;
  }

  // if no free memory avaiable, allocate new memory
  void *heap_node_addr = heap_node_alloc();
  void *addr = (void *)(heap.addr + heap.actual_size);
  add_actual_size(size);

  // then create a heap_node for the info and add this node
  heap_node *new_ptr = node_init(heap_node_addr, addr, size);
  heap_add_node(new_ptr);

  // return the address where the memory is allocated
  return addr;
}
