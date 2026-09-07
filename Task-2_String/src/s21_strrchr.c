#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *last_occurrence = s21_NULL;

  while (*str != '\0') {
    if (*str == c) {
      last_occurrence = str;
    }
    str++;
  }

  if (*str == c) {
    last_occurrence = str;
  }

  return (char *)last_occurrence;
}
