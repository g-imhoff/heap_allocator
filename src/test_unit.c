#include "./common.h"
#include "heap.h"

int main() {
  char *c = heap_alloc(100000 * sizeof(char));
  char *d = heap_alloc(140 * sizeof(char));
  char *e = heap_alloc(500 * sizeof(char));
  char *f = heap_alloc(200 * sizeof(char));
  char *g = heap_alloc(250 * sizeof(char));

  heap_free(c);
  heap_free(f);
  print_heap_node();
}
