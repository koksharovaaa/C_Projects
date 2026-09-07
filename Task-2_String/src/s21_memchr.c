#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  void *result = s21_NULL;
  s21_size_t i = 0;

  while (i < n && !result) {
    if (*p == c) result = (void *)p;
    p++;
    i++;
  }

  return result;
}