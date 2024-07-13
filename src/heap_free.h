#pragma once

#include "common.h"
#include "heap.h"
#include "heap_node.h"

void heap_free(void *addr);
void heap_unfree(void *addr);
void *heap_free_alloc(size_t size);
