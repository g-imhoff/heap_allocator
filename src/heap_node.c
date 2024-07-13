#include "heap_node.h"
#include "heap.h"

void *heap_node_alloc() {
  // send the addr for this new heap_node
  void *heap_node_addr = (void *)(heap.addr + heap.actual_size);
  // change the size of the heap in function
  heap.actual_size += sizeof(heap_node) + 1;
  return heap_node_addr;
}

heap_node *node_init(void *heap_node_addr, void *addr, size_t size) {
  // init a new heap_node depending of is addr where the memory of this node
  // will be located, and init there attribut in function
  heap_node *new_ptr = heap_node_addr;

  new_ptr->addr = addr;
  new_ptr->node_size = size;
  new_ptr->next = NULL;
  new_ptr->previous = NULL;
  new_ptr->free = false;

  return new_ptr;
}

void heap_add_node(heap_node *node_ptr) {
  // add the node_ptr a the end of the linked list contained in the heap_info
  // struct
  if (heap.heap == NULL) {
    heap.heap = node_ptr;
    return;
  }

  heap_node *tmp = heap.heap;
  while (tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = node_ptr;
  tmp->next->previous = tmp;
}

void heap_add_node_pos(heap_node *node_ptr, int pos) {
  // add the node_ptr a the pos of the linked list contained in the heap_info
  // struct
  heap_node *tmp = heap.heap;

  if (pos == 0) {
    node_ptr->next = tmp;
    tmp->previous = node_ptr;
    return;
  }

  for (int i = 1; i < pos; i++) {
    if (tmp == NULL) {
      return;
    }

    tmp = tmp->next;
  }

  if (tmp->next == NULL) {
    tmp->next = node_ptr;
    node_ptr->previous = tmp;
  } else {
    heap_node *next = tmp->next;
    tmp->next = node_ptr;
    node_ptr->next = next;
    node_ptr->previous = tmp;
    next->previous = node_ptr;
  }
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

void heap_unfree(void *addr) {
  // set the heap_node corresponding to addr that is not free anymore
  heap_node *tmp = heap.heap;

  while (tmp) {
    if (tmp->addr == addr) {
      tmp->free = false;
    }

    tmp = tmp->next;
  }
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

void *heap_free_alloc(size_t size) {
  void *addr = heap_find_smallest(size);
  heap_frag(addr, size);
  heap_unfree(addr);

  return addr;
}
