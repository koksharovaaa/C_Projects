#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *original_dest = dest;

  while (n > 0 && *src != '\0') {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  while (n > 0) {
    *dest = '\0';
    dest++;
    n--;
  }

  return original_dest;
}
