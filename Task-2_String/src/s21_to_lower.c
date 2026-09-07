#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;

  int is_valid = 1;

  if (str == s21_NULL) {
    is_valid = 0;
  }

  if (is_valid) {
    s21_size_t len = 0;
    while (str[len] != '\0') {
      len++;
    }
    result = (char *)malloc((len + 1) * sizeof(char));
    if (result == s21_NULL) {
      is_valid = 0;
    }
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        result[i] = str[i] + 32;
      } else {
        result[i] = str[i];
      }
    }
    result[len] = '\0';
  }

  return is_valid ? result : s21_NULL;
}
