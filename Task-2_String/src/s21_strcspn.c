#include "s21_string.h"

int contains_char(const char *str, char c) {
  int found = 0;
  while (*str != '\0' && !found) {
    if (*str == c) {
      found = 1;
    }
    str++;
  }
  return found;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  int found = 0;

  while (str1[count] != '\0' && !found) {
    if (contains_char(str2, str1[count])) {
      found = 1;
    } else {
      count++;
    }
  }

  return count;
}
