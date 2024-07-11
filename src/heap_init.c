#include "common.h"
#include "heap.h"

void heap_init() {
  heap.max = HEAP_MAX_SIZE;
  heap.actual_size = 0;
  heap.addr = mmap(NULL, HEAP_MAX_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  heap.heap = NULL;
}
