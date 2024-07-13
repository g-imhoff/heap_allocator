#include "my_string.h"

void str_cpy(char *str, size_t size, const char *text) {
  for (int i = 0; i < size; i++) {
    str[i] = text[i];
  }
}
