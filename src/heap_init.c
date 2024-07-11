#include "common.h"
#include "heap.h"

void heap_init() {
  heap.max = HEAP_MAX_SIZE;
  heap.actual_size = 0;
  heap.heap = NULL;
  heap.is_init = 1;
}
