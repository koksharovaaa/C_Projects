#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  int i = 0;
  while (str[i] && str[i] != c) i++;

  if (c == str[i]) result = (char *)str + i;
  return result;
}
