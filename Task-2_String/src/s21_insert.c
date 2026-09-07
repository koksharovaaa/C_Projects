#include <stdlib.h>

#include "s21_string.h"

void validate_and_calculate_lengths(const char *src, const char *str,
                                    s21_size_t start_index, s21_size_t *src_len,
                                    s21_size_t *str_len, int *is_valid) {
  *is_valid = 1;

  if (src == s21_NULL || str == s21_NULL) {
    *is_valid = 0;
  }

  *src_len = 0;
  while (*is_valid && src[*src_len] != '\0') {
    (*src_len)++;
  }

  if (*is_valid && start_index > *src_len) {
    *is_valid = 0;
  }

  *str_len = 0;
  while (*is_valid && str[*str_len] != '\0') {
    (*str_len)++;
  }
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  s21_size_t src_len = 0, str_len = 0;
  int is_valid = 1;

  validate_and_calculate_lengths(src, str, start_index, &src_len, &str_len,
                                 &is_valid);

  s21_size_t new_len = src_len + str_len;

  if (is_valid) {
    result = (char *)malloc((new_len + 1) * sizeof(char));
    if (result == s21_NULL) {
      is_valid = 0;
    }
  }

  if (is_valid) {
    for (s21_size_t i = 0; i < start_index; i++) {
      result[i] = src[i];
    }

    for (s21_size_t i = 0; i < str_len; i++) {
      result[start_index + i] = str[i];
    }

    for (s21_size_t i = start_index; i < src_len; i++) {
      result[str_len + i] = src[i];
    }

    result[new_len] = '\0';
  }

  return is_valid ? result : s21_NULL;
}
