#include "heap_node.h"

void *heap_node_alloc() {
  // send the addr for this new heap_node
  void *heap_node_addr = (void *)(heap.addr + heap.actual_size);
  // change the size of the heap in function
  add_actual_size(sizeof(heap_node));
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
