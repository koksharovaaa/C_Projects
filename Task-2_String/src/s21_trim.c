#include <stdlib.h>

#include "s21_string.h"

void calculate_bounds(const char *src, const char *trim_chars,
                      s21_size_t src_len, s21_size_t *start, s21_size_t *end) {
  s21_size_t trim_len = 0;
  while (trim_chars[trim_len] != '\0') {
    trim_len++;
  }

  *start = 0;
  while (*start < src_len) {
    int found = 0;
    for (s21_size_t i = 0; i < trim_len; i++) {
      if (src[*start] == trim_chars[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      break;
    }
    (*start)++;
  }

  *end = src_len - 1;
  while (*end >= *start) {
    int found = 0;
    for (s21_size_t i = 0; i < trim_len; i++) {
      if (src[*end] == trim_chars[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      break;
    }
    (*end)--;
  }
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;

  int is_valid = 1;

  if (src == s21_NULL || trim_chars == s21_NULL) {
    is_valid = 0;
  }

  s21_size_t src_len = 0;
  if (is_valid) {
    while (src[src_len] != '\0') {
      src_len++;
    }
  }

  if (is_valid && src_len == 0) {
    result = (char *)malloc(1);
    if (result == s21_NULL) {
      is_valid = 0;
    } else {
      result[0] = '\0';
    }
  } else if (is_valid) {
    s21_size_t start = 0, end = 0;

    calculate_bounds(src, trim_chars, src_len, &start, &end);

    s21_size_t result_len = end - start + 1;

    result = (char *)malloc((result_len + 1) * sizeof(char));
    if (result == s21_NULL) {
      is_valid = 0;
    } else {
      for (s21_size_t i = 0; i < result_len; i++) {
        result[i] = src[start + i];
      }
      result[result_len] = '\0';
    }
  }

  return is_valid ? result : s21_NULL;
}
