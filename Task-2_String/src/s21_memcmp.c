#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;
  int result = 0;

  for (s21_size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i] && !result) {
      result = p1[i] - p2[i];
    }
  }

  return result;
}
