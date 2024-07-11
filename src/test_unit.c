#include "./common.h"
#include "heap.h"

int main() {
  char *c = heap_alloc(5 * sizeof(char));

  for (int i = 0; i < 5; i++) {
    c[i] = 'a' + i;
  }

  printf("%s", c);
  printf("%ld", heap.actual_size);
}
