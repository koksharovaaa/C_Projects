#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t count = 0;
  while (str[count]) count++;
  return count;
}
