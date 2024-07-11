#include "heap_node.h"
#include "heap.h"

void *heap_node_alloc() {
  void *heap_node_addr = (void *)(heap.addr + heap.actual_size);
  heap.actual_size += sizeof(heap_node) + 1;

  return heap_node_addr;
}

heap_node *node_init(void *heap_node_addr, void *addr, size_t size) {
  heap_node *new_ptr = heap_node_addr;

  new_ptr->addr = addr;
  new_ptr->node_size = size;
  new_ptr->next = NULL;
  new_ptr->free = false;

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
    printf("This is the %d node, address : %p, size : %ld, free : %d\n", i,
           tmp->addr, tmp->node_size, tmp->free);

    tmp = tmp->next;
    i++;
  }
}

size_t heap_sizeof(void *addr) {
  heap_node *tmp = heap.heap;

  while (tmp) {
    if (tmp->addr == addr) {
      return tmp->node_size;
    }

    tmp = tmp->next;
  }

  return 0;
}

void *heap_find_smallest(size_t size) {
  heap_node *tmp = heap.heap;
  size_t smallest_of_largest_size = SIZE_MAX;
  void *address_of_smallest_largest = NULL;
  while (tmp) {
    if (tmp->free == true) {
      if (tmp->node_size > size & tmp->node_size < smallest_of_largest_size) {
        smallest_of_largest_size = tmp->node_size;
        address_of_smallest_largest = tmp->addr;
      }
    }

    tmp = tmp->next;
  }

  return address_of_smallest_largest;
}

void heap_unfree(void *addr) {
  heap_node *tmp = heap.heap;

  while (tmp) {
    if (tmp->addr == addr) {
      printf("a\n");
      tmp->free = false;
    }

    tmp = tmp->next;
  }
}

void *heap_free_alloc(size_t size) {
  void *addr = heap_find_smallest(size);
  printf("%p", addr);
  heap_unfree(addr);

  return addr;
}
