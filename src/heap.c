#include "common.h"
#include "heap.h"

// init the heap at 0 everywhere
heap_info heap = {0};

void heap_init() {
  // init the heap and is memory needed
  heap.max = HEAP_MAX_SIZE;
  heap.actual_size = 0;
  // call mmap and ask him to give him 64mb of data
  heap.addr = mmap(NULL, HEAP_MAX_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  heap.heap = NULL;
  heap.is_init = 1;
}

void add_actual_size(size_t size) {
  heap.actual_size += size + 1; // 1 additional bytes for separation
}

void print_heap_node() {
  // print all the linked list in the heap_node
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
  // get the size of a specific addr
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
  // search in the linked list heap.heap
  heap_node *tmp = heap.heap;

  // set this variable at SIZE_MAX because we are obligated to init this
  // variable for making an =< operation, with SIZE_MAX to be sure that the
  // first check of tmp->node_size =< smallest_of_largest_size is true
  size_t smallest_of_largest_size = SIZE_MAX;
  void *address_of_smallest_largest = NULL;

  while (tmp) {
    if (tmp->free == true) {
      // search an heap_node that is free and where size < tmp->node_size =<
      // smallest_of_largest_size
      if (tmp->node_size > size & tmp->node_size <= smallest_of_largest_size) {
        smallest_of_largest_size = tmp->node_size;
        address_of_smallest_largest = tmp->addr;
      }
    }

    tmp = tmp->next;
  }

  return address_of_smallest_largest;
}

void heap_frag(void *addr, size_t size_needed) {
  heap_node *tmp = heap.heap;
  int i = 0;

  while (tmp) {
    if (tmp->addr == addr) {
      void *new_node_addr = heap_node_alloc();
      heap_node *new_node = node_init(new_node_addr, addr + size_needed + 1,
                                      tmp->node_size - size_needed);
      new_node->free = true;
      heap_add_node_pos(new_node, i + 1);

      tmp->node_size -= new_node->node_size;
    }

    tmp = tmp->next;
    i++;
  }
}
