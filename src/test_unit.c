#include "./common.h"
#include "heap.h"

int main() {
  char *c = heap_alloc(5 * sizeof(char));

  for (int i = 0; i < 5; i++) {
    c[i] = 'a' + i;
  }

  printf("%s\n", c);
  printf("%ld\n", heap.actual_size);
  printf("c address : %p, heap_node address : %p\n", (void *)c,
         (void *)heap.heap);

  /*
  char *d = heap_alloc(5 * sizeof(char));

  for (int i = 0; i < 5; i++) {
    d[i] = 'f' + i;
  }

  printf("%s\n", d);
  */
}
