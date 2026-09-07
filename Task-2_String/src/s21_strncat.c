#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *p = dest;
  s21_size_t i = 0;

  for (; *p != '\0'; p++);
  for (; i < n; i++) {
    *p = src[i];
    p++;
  }
  p++;
  *p = '\0';
  return dest;
}