#include "heap_node.h"
#include "heap.h"

heap_node *node_init(void *heap_node_addr, void *addr, size_t size) {
  heap_node *new_ptr = heap_node_addr;

  new_ptr->addr = addr;
  new_ptr->node_size = size;
  new_ptr->next = NULL;

  return new_ptr;
}

void heap_add_node(heap_node *node_ptr) {
  if (heap.heap == NULL) {
    heap.heap = node_ptr;
    return;
  }

  heap_node *tmp = heap.heap;
  while (tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = node_ptr;
}

void print_heap_node() {
  heap_node *tmp = heap.heap;
  int i = 0;

  while (tmp) {
    printf("This is the %d node, address : %p, size : %ld\n", i, tmp->addr,
           tmp->node_size);

    tmp = tmp->next;
    i++;
  }
}
