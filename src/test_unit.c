#include "common.h"
#include "heap.h"
#include "heap_node.h"
#include "heap_free.h"
#include "heap_allocator.h"
#include "my_string.h"
#include <time.h>

void test_print_heap_info() {
  printf("This is the information on the heap :\n");
  printf("Is it init : %s\n", heap.is_init == 1 ? "yes" : "no");
  printf("Actual_size : %ld\n", heap.actual_size);
  printf("Does it contain free memory : %s, highest free memory : %ld\n",
         heap.contains_free_memory ? "yes" : "no", heap.highest_free_memory);
  printf("sizeof heap_node : %ld\n", sizeof(heap_node));
  printf("\n");
}

void test_fill(int *ptr, size_t size) {
  for (int i = 0; i < size; i++) {
    ptr[i] = rand();
  }
}

void malloc_test() {
  int *i = malloc(2 * sizeof(int));

  i[3] = 2; // WTF THIS WORKS ???? bro didn't thinks that handling bounds check
            // would be a good idea ?
}

void int_test() {
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

  int *i = heap_alloc(9 * sizeof(int));
  test_fill(i, 9);

  printf("Random value : c = %d, d = %d, e = %d, f = %d, g = %d, h = %d\n",
         c[11111], d[112], e[3], f[132], g[249], h[190]);
  printf("Highest memory free : %ld\n", heap.highest_free_memory);
  print_heap_node();

  // Testing that the limit works well between fragments
  printf("last element of e : %d, first element of h : %d\n", e[499], h[0]);
  printf("last element of h : %d, first element of i : %d\n", h[189], i[0]);
  printf("last element of i : %d, first element of g : %d\n", i[8], g[0]);

  // Same Test but by checking directly the address
  printf("address of last element of e : %p, Address of h : %p\n", &e[499], h);
  printf("address of last element of h : %p, Address of h : %p\n", &h[189], i);
  printf("address of last element of i : %p, Address of g : %p\n", &i[8], g);
  printf("\n");
}

void low_size_test() { char *c = heap_alloc(sizeof(char)); }

void str_test() {
  char *str1 = heap_alloc(10 * sizeof(char));
  str_cpy(str1, 10, "Salut toi");
  char *str2 = heap_alloc(20 * sizeof(char));
  str_cpy(str2, 20, "Salut toiSalut toi!");
  char *str3 = heap_alloc(30 * sizeof(char));
  str_cpy(str3, 30, "Salut toiSalut toi!Salut toi!");

  heap_free(str2);

  char *str4 = heap_alloc(15 * sizeof(char));
  str_cpy(str4, 15, "Salut toiSalut");

  print_heap_node();
  printf("%s\n", str1);
  printf("%s\n", str3);
  printf("%s\n", str4);
  printf("\n");
}

void test_frag() {
  char *str1 = heap_alloc(10 * sizeof(char));
  printf("starting address : %p\n", heap.addr);
  str_cpy(str1, 10, "Salut toi");
  char *str2 = heap_alloc(20 * sizeof(char));
  str_cpy(str2, 20, "Salut toiSalut toi!");

  heap_free(str2);

  char *str3 = heap_alloc(15 * sizeof(char));
  str_cpy(str3, 15, "Salut toiSalut");

  char *str4 = heap_alloc(30 * sizeof(char));
  str_cpy(str4, 30, "Salut toiSalut toi!Salut toi!");

  print_heap_node();
  printf("\n");
}

int main() {
  srand(time(NULL));

  test_print_heap_info();
  test_frag();
  test_print_heap_info();
}
