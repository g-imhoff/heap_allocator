#include "common.h"
#include "heap.h"

void *heap_alloc(size_t size) {
  if (!heap.is_init) {
    heap_init();
  }
}
