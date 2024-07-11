#include "./common.h"
#include "heap.h"

int main() {
  char *c = (char *)malloc(1 * sizeof(char));

  free(c);
}
