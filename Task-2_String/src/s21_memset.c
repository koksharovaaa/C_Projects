#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = str;
  s21_size_t i = 0;

  for (; i < n; i++) {
    p[i] = c;
  }

  return str;
}