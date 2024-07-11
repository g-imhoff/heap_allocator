#include "./common.h"
#include "heap.h"
#include <stdlib.h>
#include <time.h>

void test_fill(int *ptr, size_t size) {
  for (int i = 0; i < size; i++) {
    ptr[i] = rand();
  }
}

int main() {
  srand(time(NULL));
  int r = rand();

  int *c = heap_alloc(100000 * sizeof(int));
  test_fill(c, 100000);

  int *d = heap_alloc(140 * sizeof(int));
  test_fill(d, 140);

  int *e = heap_alloc(500 * sizeof(int));
  test_fill(e, 500);

  int *f = heap_alloc(200 * sizeof(int));
  test_fill(f, 200);

  int *g = heap_alloc(250 * sizeof(int));
  test_fill(g, 250);

  heap_free(c);
  heap_free(f);

  int *h = heap_alloc(190 * sizeof(int));
  test_fill(h, 190);

  print_heap_node();
  printf("Random value : c = %d, d = %d, e = %d, f = %d, g = %d, h = %d\n",
         c[11111], d[112], e[3], f[132], g[249], h[190]);
  printf("Highest memory free : %ld\n", heap.highest_free_memory);
}
